//
// Created by Kacper Skelnik on 19.01.2025.
//

#include "Grid.h"

#include "../globals/Resource.h"
#include "../globals/Screen.h"
#include "../globals/Settings.h"
#include <iostream>

Grid::Grid(const unsigned cols, const unsigned rows): cols(cols), rows(rows) {
}

int Grid::getIndex(const unsigned col, const unsigned row) const {
    return col + row * cols;
}

sf::priv::Vector4<float> Grid::invertMatrix(const sf::priv::Vector4<float> matrix) {
    const float det = 1 / (matrix.x * matrix.w - matrix.y * matrix.z);
    return {
        det * matrix.w,
        -det * matrix.y,
        -det * matrix.z,
        det * matrix.x,
    };
}

sf::Vector2u Grid::getGridPosition(const float posX, const float posY) const {
    using namespace Settings;

    const sf::priv::Vector4 invertedMatrix = invertMatrix({
        iX * 0.5f * Variables::getSpriteWidth(),
        jX * 0.5f * Variables::getSpriteWidth(),
        iY * 0.5f * Variables::getSpriteHeight(),
        jY * 0.5f * Variables::getSpriteHeight(),
    });

    return {
        static_cast<unsigned>(posX * invertedMatrix.x + posY * invertedMatrix.y),
        static_cast<unsigned>(posX * invertedMatrix.z + posY * invertedMatrix.w)
    };
}

sf::Vector2f Grid::getScreenPosition(const unsigned col, const unsigned row) const {
    using namespace Settings;

    const float screenX =
        (static_cast<float>(col) * iX + static_cast<float>(row) * jX) * Variables::getSpriteWidth() * 0.5f;
    const float screenY =
        (static_cast<float>(col) * iY + static_cast<float>(row) * jY) * Variables::getSpriteHeight() * 0.5f;

    return {screenX - Variables::getSpriteWidth() / 2, screenY};
}

BuildingType Grid::getBuildingFrom(const unsigned col, const unsigned row) const {
    return static_cast<BuildingType>(state->buildingsGrid[getIndex(col, row)]);
}

CharacterType Grid::getCharacterFrom(const unsigned col, const unsigned row) const {
    return static_cast<CharacterType>(state->charactersGrid[getIndex(col, row)]);
}

EnvironmentType Grid::getEnvironmentFrom(const unsigned col, const unsigned row) const {
    return static_cast<EnvironmentType>(state->environmentGrid[getIndex(col, row)]);
}

sf::Vector2f Grid::getCenterPosition(const sf::Texture& texture, const sf::Vector2f position) {
    using namespace Settings;

    const float centeredX =
        position.x + (Variables::getSpriteWidth() / 2.0f) - static_cast<float>(texture.getSize().x) / 2.0f;
    const float centeredY =
        position.y + (Variables::getSpriteHeight() / 2.0f) - static_cast<float>(texture.getSize().y);

    return {centeredX, centeredY};
}

// Implements Moore Neighbors
std::vector<GridPosition> Grid::getNeighbors(const GridPosition& position) const {
    std::vector<GridPosition> neighbors;
    neighbors.reserve(8); // max number of neighbors

    for (int dy = 1; dy >= -1; dy--) {
        for (int dx = 1; dx >= -1; dx--) {
            if (dx == 0 && dy == 0) continue; // skip center cell

            const int nCol = position.column + dx;
            const int nRow = position.row + dy;

            if (nCol >= 0 && nCol < cols && nRow >= 0 && nRow < rows) {
                neighbors.emplace_back(nRow, nCol);
            }
        }
    }

    return neighbors;
}

void Grid::draw(const std::optional<BuildingType>& maybeSelectedBuilding) const {
    using namespace Screen;
    using namespace Settings;
    using namespace Resource;

    Window::mainViewFocus();

    std::optional<unsigned> maybeSelectedCol = std::nullopt;
    std::optional<unsigned> maybeSelectedRow = std::nullopt;
    if (maybeSelectedBuilding) {
        const sf::Vector2i mousePosition = sf::Mouse::getPosition(Window::get());
        const sf::Vector2f worldPosition = Window::get().mapPixelToCoords(mousePosition);
        const sf::Vector2u gridPosition  = getGridPosition(worldPosition.x, worldPosition.y);
        maybeSelectedCol.emplace(gridPosition.x);
        maybeSelectedRow.emplace(gridPosition.y);
    }

    for (int i = 0; i < cols; i++) {
        for (int j = 0; j < rows; j++) {
            const OccupationType occupation = checkOccupation(i, j);
            sf::Vector2f         position   = getScreenPosition(i, j);

            const EnvironmentType     environment = getEnvironmentFrom(i, j);
            sf::Sprite                sprite(getEnvironmentTexture(environment));
            std::optional<sf::Sprite> buildingToBuildSprite = std::nullopt;
            if (maybeSelectedCol && maybeSelectedCol.value() == i && maybeSelectedRow && maybeSelectedRow.value() ==
                j) {
                position.y += -Variables::getSpriteHeight() * 0.1f;
                if (occupation == BuildingOccupation) {
                    sprite.setTexture(Textures::getGround());
                } else {
                    const sf::Texture& texture = getBuildingTexture(maybeSelectedBuilding.value());
                    buildingToBuildSprite.emplace(sf::Sprite(texture));
                    buildingToBuildSprite->setPosition(getCenterPosition(texture, position));
                }
            }
            sprite.setPosition(position);
            Window::get().draw(sprite);
            if (buildingToBuildSprite) {
                Window::get().draw(buildingToBuildSprite.value());
            }

            if (occupation == BuildingOccupation) {
                const BuildingType building = getBuildingFrom(i, j);
                const sf::Texture& texture  = getBuildingTexture(building);
                sf::Sprite         buildingSprite(texture);
                buildingSprite.setPosition(getCenterPosition(texture, position));
                Window::get().draw(buildingSprite);
            }
            if (occupation == CharacterOccupation) {
                const CharacterType character = getCharacterFrom(i, j);
                const sf::Texture&  texture   = getCharacterTexture(character);
                sf::Sprite          characterSprite(getCharacterTexture(character));
                characterSprite.setPosition(getCenterPosition(texture, position));
                Window::get().draw(characterSprite);
            }
        }
    }
}

OccupationType Grid::checkOccupation(const unsigned col, const unsigned row) const {
    // Bounds check
    if (col >= cols || row >= rows) {
        return Bound;
    }

    // Cells occupation
    if (state->buildingsGrid[getIndex(col, row)]) {
        return BuildingOccupation;
    }
    if (state->charactersGrid[getIndex(col, row)]) {
        return CharacterOccupation;
    }

    return Free;
}

std::optional<GridPosition> Grid::addBuilding(const BuildingType buildingType, const sf::Vector2i& position) const {
    using namespace Settings;
    using namespace Screen;

    Window::mainViewFocus();
    const sf::Vector2f worldPosition = Window::get().mapPixelToCoords(position);
    const auto         [col, row]    = getGridPosition(worldPosition.x, worldPosition.y);

    const OccupationType                 occupation          = checkOccupation(col, row);
    const std::optional<EnvironmentType> requiredEnvironment = getRequiredEnvironment(buildingType);
    const EnvironmentType                cellsEnvironment    = getEnvironmentFrom(col, row);

    if (occupation == Free && (!requiredEnvironment.has_value() || cellsEnvironment == requiredEnvironment.value())) {
        state->buildingsGrid[getIndex(col, row)] = buildingType;
        GridPosition gridPos                     = {row, col};
        return gridPos;
    }
    return std::nullopt;
}

std::optional<sf::Sprite> Grid::getBuildingSprite(const GridPosition& position) const {
    const OccupationType occupation = checkOccupation(position.column, position.row);
    if (occupation == BuildingOccupation) {
        const BuildingType building = getBuildingFrom(position.column, position.row);
        const sf::Texture& texture  = getBuildingTexture(building);
        sf::Sprite         buildingSprite(texture);
        const sf::Vector2f screenPosition = getScreenPosition(position.column, position.row);
        buildingSprite.setPosition(getCenterPosition(texture, screenPosition));

        return buildingSprite;
    }
    return std::nullopt;
}

std::optional<GridPosition> Grid::addCharacter(const CharacterType characterType,
                                               const GridPosition& schoolPosition) const {
    for (const GridPosition neighbor : getNeighbors(schoolPosition)) {
        const OccupationType occupation = checkOccupation(neighbor.column, neighbor.row);
        if (occupation == Free) {
            state->charactersGrid[getIndex(neighbor.column, neighbor.row)] = characterType;
            return neighbor;
        }
    }
    return std::nullopt;
}

// Implements Dijkstra's algorithm to find a path from start to goal
std::vector<GridPosition> Grid::dijkstraPath(const GridPosition& start, const GridPosition& goal) const {
    using PQItem = std::pair<int, GridPosition>; // priority queue item(distance, position)
    struct CompareDistance {
        bool operator()(const PQItem& a, const PQItem& b) const {
            return a.first > b.first; // min-heap on distance
        }
    };

    std::priority_queue<PQItem, std::vector<PQItem>, CompareDistance> queue;
    std::unordered_map<GridPosition, GridPosition> cameFrom;
    std::vector<int> distance(cols * rows, std::numeric_limits<int>::max());

    const int startIdx = getIndex(start.column, start.row);
    distance[startIdx] = 0;
    queue.emplace(0, start);

    while (!queue.empty()) {
        auto [dist, current] = queue.top();
        queue.pop();

        if (current == goal) {
            // Reconstruct a path
            std::vector<GridPosition> path;
            GridPosition              position = goal;
            while (position != start) {
                path.push_back(position);
                position = cameFrom[position];
            }
            std::ranges::reverse(path);
            return path;
        }

        // Skip if we already found a better path to this node
        if (dist > distance[getIndex(current.column, current.row)]) {
            continue;
        }

        for (GridPosition neighbor : getNeighbors(current)) {
            const OccupationType occupation = checkOccupation(neighbor.column, neighbor.row);
            if (occupation == Free || neighbor == goal) {
                const int neighborIdx = getIndex(neighbor.column, neighbor.row);
                // Here it assumes cost = 1 per move; modify if terrain has weights
                int newDist = dist + 1;
                if (newDist < distance[neighborIdx]) {
                    distance[neighborIdx] = newDist;
                    cameFrom[neighbor]    = current;
                    queue.emplace(newDist, neighbor);
                }
            }
        }
    }

    return {}; // No path found
}

std::optional<GridPosition> Grid::moveCharacter(const GridPosition& sourcePosition,
                                                const GridPosition& destinationPosition) const {
    const std::vector<GridPosition> path = dijkstraPath(sourcePosition, destinationPosition);
    if (path.empty()) {
        return std::nullopt; // No path found
    }

    const CharacterType type = getCharacterFrom(sourcePosition.column, sourcePosition.row);
    state->charactersGrid[getIndex(sourcePosition.column, sourcePosition.row)] = 0;
    state->charactersGrid[getIndex(path[0].column, path[0].row)] = type;

    return GridPosition{path[0].row, path[0].column};
}
