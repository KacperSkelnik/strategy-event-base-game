#pragma once

#include "../../events/EventEntity.h"
#include "../GridPosition.h"
#include "BuildingType.h"

class Building: public EventEntity {
  private:
    BuildingType type;
    GridPosition position;
    bool         factory;

  public:
    Building() = delete;
    explicit Building(BuildingType type, GridPosition position, bool isFactory);
    explicit Building(BuildingType type, GridPosition position);
    ~Building() override = default;

    [[nodiscard]] BuildingType getType() const { return type; }
    [[nodiscard]] GridPosition getPosition() const { return position; }
    [[nodiscard]] bool         isFactory() const { return factory; }
};