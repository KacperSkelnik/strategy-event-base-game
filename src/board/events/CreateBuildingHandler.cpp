//
// Created by Kacper Skelnik on 16.04.2025.
//

#include "CreateBuildingHandler.h"

CreateBuildingHandler::CreateBuildingHandler(const BuildingType selectedBuilding, const GridPosition position):
    selectedBuilding(selectedBuilding),
    position(position) {}

void CreateBuildingHandler::invoke(const std::shared_ptr<Board> target) {
    Building building(selectedBuilding, position);
    target->createBuilding(std::make_shared<Building>(building));
}