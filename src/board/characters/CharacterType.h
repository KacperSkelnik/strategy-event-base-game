#pragma once

#include "../../globals/Resource.h"
#include "SFML/Graphics/Texture.hpp"

typedef enum CharacterType {
    Serf = 1,
} CharacterType;

inline sf::Texture& getCharacterTexture(const CharacterType type) {
    using namespace Resource;

    switch (type) {
        default:
            return Textures::getSerf();
    }
}