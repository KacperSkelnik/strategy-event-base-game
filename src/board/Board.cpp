//
// Created by Kacper Skelnik on 16.04.2025.
//

#include "Board.h"

Board::Board(const std::shared_ptr<Grid>& grid): grid(grid) {
    buildings.reserve(32);
}

void Board::createBuilding(const BuildingType buildingType, const sf::Vector2i& position) {
    const std::optional<GridPosition> maybePosition = grid->addBuilding(buildingType, position);
    if (maybePosition) {
        Building building(buildingType, maybePosition.value());
        buildings.emplace_back(std::make_shared<Building>(building));
    }
}