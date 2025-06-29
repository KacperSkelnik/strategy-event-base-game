#pragma once
#include "../board/buildings/BuildingType.h"
#include "../board/characters/CharacterType.h"
#include "../board/GridPosition.h"
#include "../economy/EconomyResource.h"
#include "SFML/System/Vector2.hpp"
#include <variant>

struct CreateBuildingParams {
    BuildingType selectedBuilding;
    sf::Vector2i position;
};

struct SpendResourceParams {
    EconomyResource resource;
    int             amount;
};

struct CreateCharacterParams {
    CharacterType characterType;
    GridPosition  sourcePosition;
};

using EventParams = std::variant<std::monostate, CreateBuildingParams, SpendResourceParams, CreateCharacterParams>;