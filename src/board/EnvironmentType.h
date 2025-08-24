#pragma once

#include "../globals/Resource.h"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/System/Vector2.hpp"

typedef enum EnvironmentType {
    Grass = 0,
    GoldRock = 1,
    Road = 2,
} EnvironmentType;

inline sf::Texture& getEnvironmentTexture(const EnvironmentType type) {
    using namespace Resource;

    switch (type) {
        case Grass:
            return Textures::getGrass();
        case GoldRock:
            return Textures::getGoldRock();
        case Road:
            return Textures::getRoad();
        default:
            return Textures::getGround();
    }
}