#pragma once

#include "../../economy/EconomyResource.h"
#include "../../events/EventEntity.h"
#include "../GridPosition.h"
#include "BuildingType.h"

class Building: public EventEntity {
  private:
    BuildingType type;
    GridPosition position;

  public:
    Building() = delete;
    explicit Building(BuildingType type, GridPosition position);
    ~Building() override = default;

    [[nodiscard]] BuildingType getType() const { return type; }
    [[nodiscard]] GridPosition getPosition() const { return position; }
};