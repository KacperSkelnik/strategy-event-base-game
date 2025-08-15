//
// Created by Kacper Skelnik on 01.02.2025.
//

#include "Building.h"

Building::Building(const BuildingType type, const GridPosition position, const bool isFactory):
    type(type),
    position(position),
    factory(isFactory) {}

Building::Building(const BuildingType type, const GridPosition position):
    type(type),
    position(position),
    factory(false) {}
