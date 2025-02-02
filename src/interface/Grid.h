#pragma once

#include "../board/BuildingType.h"
#include "GridPosition.h"
#include <SFML/Graphics.hpp>

class Grid {
  private:
    int                rows, cols;
    sf::RectangleShape line;
    sf::RectangleShape selectedCell;
    std::vector<bool>  grid; // state of occupied cells

    unsigned            getGridColumn(float posX) const;
    unsigned            getGridRow(float posY) const;
    static sf::Vector2f getCellPosition(unsigned row, unsigned col);

  public:
    Grid() = default;
    explicit Grid(int rows, int cols);
    ~Grid() = default;

    void                        draw(const std::optional<BuildingType>& maybeSelectedBuilding);
    bool                        canBuildingBePlaced(unsigned row, unsigned col, const sf::Vector2i& size) const;
    std::optional<GridPosition> addBuilding(BuildingType buildingType, const sf::Vector2i& position);
};