#pragma once

#include "../events/EventEntity.h"
#include "../interface/GridPosition.h"
#include "BuildingType.h"

class Building final: public EventEntity {
  private:
    BuildingType type;
    bool         isSelected;
    GridPosition position;

  public:
    Building() = delete;
    explicit Building(BuildingType type, GridPosition position);
    ~Building() override = default;
};