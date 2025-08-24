//
// Created by Kacper Skelnik on 24.08.2025.
//
#include "CreateRoadHandler.h"

CreateRoadHandler::CreateRoadHandler(const CreateRoadParams& params): params(params) {
}

bool CreateRoadHandler::invoke(const std::shared_ptr<Board> target) {
    return target->createRoad(params.position);
}