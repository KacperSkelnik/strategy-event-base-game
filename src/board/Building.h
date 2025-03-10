#pragma once

#include "../interface/GridPosition.h"
#include "BuildingType.h"

class Building {
  private:
    BuildingType type;
    bool         isSelected;
    GridPosition position;

  public:
    Building() = delete;
    explicit Building(BuildingType type, GridPosition position);
    ~Building() = default;
};