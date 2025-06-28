#pragma once
#include "../board/BuildingType.h"
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

using EventParams = std::variant<std::monostate, CreateBuildingParams, SpendResourceParams>;