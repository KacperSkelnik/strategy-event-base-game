//
// Created by Kacper Skelnik on 19.01.2025.
//

#include "Grid.h"

#include "../globals/Scene.h"
#include "../globals/Settings.h"
#include <iostream>

Grid::Grid(const int rows, const int cols): rows(rows), cols(cols) {
    line.setFillColor(sf::Color::Black);
    selectedCell.setFillColor(sf::Color::Transparent);
    selectedCell.setOutlineThickness(2);
    grid = std::vector(rows * cols, false);
}

void Grid::draw(const std::optional<BuildingType>& maybeSelectedBuilding) {
    using namespace Scene;
    using namespace Settings;

    if (maybeSelectedBuilding) {
        const sf::Vector2i mousePosition = sf::Mouse::getPosition(Window::get());
        const unsigned     row           = getGridRow(static_cast<float>(mousePosition.y));
        const unsigned     col           = getGridColumn(static_cast<float>(mousePosition.x));
        const sf::Vector2i size          = getBuildingsCells(maybeSelectedBuilding.value());

        const float cellSize = Variables::getCellSize();
        selectedCell.setSize({static_cast<float>(size.x) * cellSize, static_cast<float>(size.y) * cellSize});
        selectedCell.setPosition(getCellPosition(row, col));

        Window::mainViewFocus();
        if (canBuildingBePlaced(row, col, size)) {
            selectedCell.setOutlineColor(sf::Color::Black);
        } else {
            selectedCell.setOutlineColor(sf::Color::Red);
        }
        Window::get().draw(selectedCell);
    }
}

unsigned Grid::getGridColumn(const float posX) const {
    using namespace Settings;

    const float cellSize = Variables::getCellSize();
    return static_cast<unsigned>(std::min(posX / cellSize, static_cast<float>(cols) - 1));
}

unsigned Grid::getGridRow(const float posY) const {
    using namespace Settings;

    const float cellSize = Variables::getCellSize();
    return static_cast<unsigned>(std::min(posY / cellSize, static_cast<float>(rows) - 1));
}

sf::Vector2f Grid::getCellPosition(const unsigned row, const unsigned col) {
    using namespace Settings;

    const float cellSize = Variables::getCellSize();
    return {static_cast<float>(col) * cellSize, static_cast<float>(row) * cellSize};
}

bool Grid::canBuildingBePlaced(const unsigned row, const unsigned col, const sf::Vector2i& size) const {
    for (size_t i = 0; i < size.y; i++) {
        for (size_t j = 0; j < size.x; j++) {
            const unsigned newRow = row + i;
            const unsigned newCol = col + j;

            // Bounds check
            if (newRow >= rows || newCol >= cols) {
                return false;
            }

            // Cells occupation
            if (grid[newRow * cols + newCol]) {
                return false;
            }
        }
    }
    return true;
}

std::optional<GridPosition> Grid::addBuilding(const BuildingType buildingType, const sf::Vector2i& position) {
    using namespace Settings;

    const unsigned row = getGridRow(static_cast<float>(position.y));
    const unsigned col = getGridColumn(static_cast<float>(position.x));

    const sf::Vector2i size = getBuildingsCells(buildingType);

    if (canBuildingBePlaced(row, col, size)) {
        for (size_t i = 0; i < size.y; i++) {
            for (size_t j = 0; j < size.x; j++) {
                const unsigned newRow        = row + i;
                const unsigned newCol        = col + j;
                grid[newRow * cols + newCol] = true;
            }
        }

        GridPosition gridPos = {row, col};
        return gridPos;
    }
    return std::nullopt;
}