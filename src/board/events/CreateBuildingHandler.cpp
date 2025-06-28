//
// Created by Kacper Skelnik on 16.04.2025.
//

#include "CreateBuildingHandler.h"

CreateBuildingHandler::CreateBuildingHandler(const CreateBuildingParams& params): params(params) {}

bool CreateBuildingHandler::invoke(const std::shared_ptr<Board> target) {
    return target->createBuilding(params.selectedBuilding, params.position);
}