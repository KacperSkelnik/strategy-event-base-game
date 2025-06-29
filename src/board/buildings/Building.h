#pragma once

#include "../../events/EventEntity.h"
#include "../GridPosition.h"
#include "BuildingType.h"

class Building final: public EventEntity {
  private:
    BuildingType type;
    GridPosition position;

  public:
    Building() = delete;
    explicit Building(BuildingType type, GridPosition position);
    ~Building() override = default;

    BuildingType getType() const { return type; }
    GridPosition getPosition() const { return position; }
};