#pragma once

#include "../../economy/EconomyResource.h"
#include "../../globals/Resource.h"
#include "../EnvironmentType.h"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/System/Vector2.hpp"
#include <optional>

enum BuildingType {
    TownHall        = 1,
    School          = 2,
    Farm            = 3,
    GoldMine        = 4,
    Quarry          = 5,
    LumberjackHouse = 6,
    SawMill         = 7,
    Tower           = 8,
};

inline sf::Texture& getBuildingTexture(const BuildingType type) {
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

inline std::optional<EnvironmentType> getRequiredEnvironment(const BuildingType type) {
    switch (type) {
        case GoldMine:
            return GoldRock;
        default:
            return std::nullopt;
    }
}

inline std::optional<EconomyResource> getProducedResource(const BuildingType type) {
    switch (type) {
        case GoldMine:
            return Gold;
        default:
            return std::nullopt;
    }
}

inline bool isFactory(const BuildingType type) {
    switch (type) {
        case TownHall:
        case School:
        case Tower:
            return false;
        default:
            return true;
    }
}