#pragma once

#include "../interface/GridPosition.h"
#include "BuildingType.h"
#include "SFML/Graphics/CircleShape.hpp"
#include "SFML/Graphics/RectangleShape.hpp"

class Building {
  private:
    BuildingType                   type;
    sf::RectangleShape             rect;
    std::optional<sf::CircleShape> range;
    bool                           isSelected;
    GridPosition                   position;

    void drawBuilding() const;
    void drawRange() const;

  public:
    explicit Building(BuildingType type, GridPosition position);
    ~Building() = default;

    void recalculatePosition();
    void recalculateSize();
    void draw() const;
};