#pragma once

#include "../globals/Resource.h"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/System/Vector2.hpp"

typedef enum EnvironmentType {
    Grass    = 0,
    GoldRock = 1,
} EnvironmentType;

inline sf::Texture& getEnvironmentTexture(const EnvironmentType type) {
    using namespace Resource;

    switch (type) {
        case Grass:
            return Textures::getGrass();
        case GoldRock:
            return Textures::getGoldRock();
        default:
            return Textures::getGround();
    }
}