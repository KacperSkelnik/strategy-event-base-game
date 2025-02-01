#pragma once

#include "../board/Building.h"
#include <SFML/Graphics.hpp>
#include <vector>

class Grid {
  private:
    int                                    rows, cols;
    float                                  cellSize;
    sf::RectangleShape                     line;
    sf::RectangleShape                     selectedCell;
    std::vector<std::unique_ptr<Building>> objects;

    unsigned            getGridColumn(float posX, float cellSize) const;
    unsigned            getGridRow(float posY, float cellSize) const;
    static sf::Vector2f getCellPosition(unsigned row, unsigned col, float cellSize);

  public:
    Grid() = default;
    explicit Grid(int rows, int cols, float cellSize);
    void  draw();
    void  addBuilding(std::unique_ptr<Building> building);
    float getCellSize() const;
};