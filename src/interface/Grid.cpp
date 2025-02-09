//
// Created by Kacper Skelnik on 19.01.2025.
//

#include "Grid.h"

#include "../globals/Resource.h"
#include "../globals/Scene.h"
#include "../globals/Settings.h"

Grid::Grid(const unsigned cols, const unsigned rows): cols(cols), rows(rows) {
    grid = std::vector(cols * rows, 0);
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

    const float screenX = (static_cast<float>(col) * iX + static_cast<float>(row) * jX) * Variables::getSpriteWidth() * 0.5f;
    const float screenY = (static_cast<float>(col) * iY + static_cast<float>(row) * jY) * Variables::getSpriteHeight() * 0.5f;
    return {screenX - Variables::getSpriteWidth() / 2, screenY};
}

BuildingType Grid::getBuildingFrom(const unsigned col, const unsigned row) const {
    return static_cast<BuildingType>(grid[col + row * cols]);
}

sf::Vector2f Grid::getBuildingPosition(const BuildingType building, const sf::Vector2f position) {
    using namespace Settings;

    const float centeredX = position.x + (Variables::getSpriteWidth() / 2.0f) -
                            static_cast<float>(getBuildingsTexture(building).getSize().x) / 2.0f;
    const float centeredY = position.y + (Variables::getSpriteHeight() / 2.0f) -
                            static_cast<float>(getBuildingsTexture(building).getSize().y);

    return {centeredX, centeredY};
}

void Grid::draw(const std::optional<BuildingType>& maybeSelectedBuilding) const {
    using namespace Scene;
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
            const bool   isOccupied = isCellOccupied(i, j);
            sf::Vector2f position   = getScreenPosition(i, j);
            sf::Sprite   sprite(Textures::getGrass());
            if (maybeSelectedCol && maybeSelectedCol.value() == i && maybeSelectedRow && maybeSelectedRow.value() == j) {
                position.y += -Variables::getSpriteHeight() * 0.1f;
                if (isOccupied) {
                    sprite.setTexture(Textures::getGround());
                }
            }
            sprite.setPosition(position);
            Window::get().draw(sprite);

            if (isOccupied) {
                const BuildingType building = getBuildingFrom(i, j);
                sf::Sprite         buildingSprite(getBuildingsTexture(building));
                buildingSprite.setPosition(getBuildingPosition(building, position));
                Window::get().draw(buildingSprite);
            }
        }
    }
}

bool Grid::isCellOccupied(const unsigned col, const unsigned row) const {
    // Bounds check
    if (col >= cols || row >= rows) {
        return true;
    }

    // Cells occupation
    if (grid[col + row * cols]) {
        return true;
    }

    return false;
}

std::optional<GridPosition> Grid::addBuilding(const BuildingType buildingType, const sf::Vector2i& position) {
    using namespace Settings;
    using namespace Scene;

    Window::mainViewFocus();
    const sf::Vector2f worldPosition = Window::get().mapPixelToCoords(position);
    const auto [col, row]            = getGridPosition(worldPosition.x, worldPosition.y);
    if (!isCellOccupied(col, row)) {
        grid[col + row * cols] = buildingType;
        GridPosition gridPos   = {row, col};
        return gridPos;
    }
    return std::nullopt;
}