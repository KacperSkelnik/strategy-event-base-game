#pragma once

#include "../board/buildings/BuildingType.h"
#include "../board/buildings/Building.h"
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
    CharacterType             characterType;
    std::shared_ptr<Building> school;
};

struct GoForResourceParams {
    GridPosition resourcePosition;
};

// clang-format off
using EventParams = std::variant<
    std::monostate,
    CreateBuildingParams,
    SpendResourceParams,
    CreateCharacterParams,
    GoForResourceParams
>;
// clang-format on