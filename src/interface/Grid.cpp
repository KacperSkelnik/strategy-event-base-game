//
// Created by Kacper Skelnik on 19.01.2025.
//

#include "Grid.h"

#include "../globals/Scene.h"
#include <iostream>

unsigned Grid::getGridColumn(
    const float posX,
    const float cellSize
) const {
    return static_cast<unsigned>(std::min(posX / cellSize, static_cast<float>(cols) - 1));
}

unsigned Grid::getGridRow(
    const float posY,
    const float cellSize
) const {
    return static_cast<unsigned>(std::min(posY / cellSize, static_cast<float>(rows) - 1));
}

sf::Vector2f Grid::getCellCenter(
    const unsigned row,
    const unsigned col,
    const float    cellSize
) {
    return {static_cast<float>(col) * cellSize + cellSize / 2, static_cast<float>(row) * cellSize + cellSize / 2};
}

void Grid::draw() {
    using namespace Scene;

    const sf::Vector2i mousePosition = sf::Mouse::getPosition(Window::get());
    const unsigned     row           = getGridRow(mousePosition.y, cellSize);
    const unsigned     col           = getGridColumn(mousePosition.x, cellSize);
    selectedCell.setPosition({static_cast<float>(col) * cellSize, static_cast<float>(row) * cellSize});

    Window::mainViewFocus();

    // Drawing cell selector
    Window::get().draw(selectedCell);

    // Drawing objects
    for (auto& obj : objects) {
        Window::get().draw(*obj);
    }
}

void Grid::addObject(std::unique_ptr<sf::Shape> object) {
    const sf::Vector2f  position = object->getPosition();
    const sf::FloatRect bounds   = object->getGlobalBounds();

    const unsigned row = getGridRow(position.y, cellSize);
    const unsigned col = getGridColumn(position.x, cellSize);
    auto [x, y]        = getCellCenter(row, col, cellSize);

    object->setPosition({x - bounds.size.x / 2, y - bounds.size.y / 2});

    objects.push_back(std::move(object));
}