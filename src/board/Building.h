#pragma once

#include "SFML/Graphics/CircleShape.hpp"
#include "SFML/Graphics/RectangleShape.hpp"

enum BuildingType {
    TownHall,
    School,
    Farm,
    GoldMine,
    Quarry,
    LumberjackHouse,
    SawMill,
    Tower,
};

class Building {
  private:
    BuildingType                   type;
    sf::RectangleShape             rect;
    std::optional<sf::CircleShape> range;
    bool                           isSelected;

    void drawBuilding() const;
    void drawRange() const;

  public:
    // TODO: replace with getTexture - probably as a part of globals
    static sf::Color    getColor(BuildingType type);
    static sf::Vector2i getCells(BuildingType type);

    explicit Building(BuildingType type, const sf::Vector2f& size, const sf::Vector2f& position);
    ~Building() = default;

    void draw() const;
};