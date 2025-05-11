//
// Created by Kacper Skelnik on 16.04.2025.
//

#include "CreateBuildingHandler.h"

CreateBuildingHandler::CreateBuildingHandler(const BuildingType selectedBuilding, const sf::Vector2i& position):
    selectedBuilding(selectedBuilding),
    position(position) {}

void CreateBuildingHandler::invoke(const std::shared_ptr<Board> target) {
    target->createBuilding(selectedBuilding, position);
}