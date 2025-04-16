//
// Created by Kacper Skelnik on 16.04.2025.
//

#include "Board.h"

Board::Board() {
    buildings.reserve(32);
}

void Board::createBuilding(const std::shared_ptr<Building>& building) {
    buildings.emplace_back(building);
}