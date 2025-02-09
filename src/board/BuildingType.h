#pragma once

#include "../globals/Resource.h"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/System/Vector2.hpp"
#include <optional>

typedef enum BuildingType {
    None,
    TownHall,
    School,
    Farm,
    GoldMine,
    Quarry,
    LumberjackHouse,
    SawMill,
    Tower,
} BuildingType;

inline sf::Texture& getBuildingsTexture(const BuildingType type) {
    using namespace Resource;

    switch (type) {
        case TownHall:
            return Textures::getTownHall();
        case School:
            return Textures::getSchool();
        case Farm:
            return Textures::getFarm();
        case GoldMine:
            return Textures::getGoldMine();
        case Quarry:
            return Textures::getQuarry();
        case LumberjackHouse:
            return Textures::getLumberjackHouse();
        case SawMill:
            return Textures::getSawMill();
        case Tower:
            return Textures::getTower();
        default:
            return Textures::getGround();
    }
}

inline sf::Vector2i getBuildingsCells(const BuildingType type) {
    switch (type) {
        case TownHall:
        case School:
            return {3, 3};
        case Farm:
            return {4, 4};
        case GoldMine:
        case Quarry:
        case SawMill:
            return {2, 2};
        case LumberjackHouse:
        case Tower:
            return {1, 1};
        default:
            return {0, 0};
    }
}

inline std::optional<float> getBuildingsRange(const BuildingType type) {
    switch (type) {
        case Tower:
            return 6;
        default:
            return std::nullopt;
    }
}