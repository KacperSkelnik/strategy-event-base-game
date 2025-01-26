//
// Created by Kacper Skelnik on 19.01.2025.
//

#ifndef GRID_H
#define GRID_H
#include <SFML/Graphics.hpp>
#include <vector>

class Grid {
  private:
    int                                     rows, cols;
    float                                   cellSize;
    sf::RectangleShape                      line;
    sf::RectangleShape                      selectedCell;
    std::vector<std::unique_ptr<sf::Shape>> objects;

    unsigned            getGridColumn(float posX, float cellSize) const;
    unsigned            getGridRow(float posY, float cellSize) const;
    static sf::Vector2f getCellCenter(unsigned row, unsigned col, float cellSize);

  public:
    Grid() = default;
    explicit Grid(const int rows, const int cols, const float cellSize);
    void draw();
    void addObject(std::unique_ptr<sf::Shape> object);
};

#endif // GRID_H
