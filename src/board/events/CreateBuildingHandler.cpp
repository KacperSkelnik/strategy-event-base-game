//
// Created by Kacper Skelnik on 16.04.2025.
//

#include "CreateBuildingHandler.h"

CreateBuildingHandler::CreateBuildingHandler(const CreateBuildingParams& params): params(params) {}

void CreateBuildingHandler::invoke(const std::shared_ptr<Board> target) {
    target->createBuilding(params.selectedBuilding, params.position);
}