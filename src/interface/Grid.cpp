//
// Created by Kacper Skelnik on 19.01.2025.
//

#include "Grid.h"

#include "../globals/Scene.h"
#include <iostream>

Grid::Grid(const int rows, const int cols, const float cellSize): rows(rows), cols(cols), cellSize(cellSize) {
    line.setFillColor(sf::Color::Black);
    selectedCell.setSize(sf::Vector2f(cellSize, cellSize));
    selectedCell.setFillColor(sf::Color::Transparent);
    selectedCell.setOutlineColor(sf::Color::Black);
    selectedCell.setOutlineThickness(2);
}

unsigned Grid::getGridColumn(const float posX, const float cellSize) const {
    return static_cast<unsigned>(std::min(posX / cellSize, static_cast<float>(cols) - 1));
}

unsigned Grid::getGridRow(const float posY, const float cellSize) const {
    return static_cast<unsigned>(std::min(posY / cellSize, static_cast<float>(rows) - 1));
}

sf::Vector2f Grid::getCellPosition(const unsigned row, const unsigned col, const float cellSize) {
    return {static_cast<float>(col) * cellSize, static_cast<float>(row) * cellSize};
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
    for (const auto& obj : objects) {
        obj->draw();
    }
}

void Grid::addBuilding(std::unique_ptr<Building> building) {
    const sf::Vector2f position = building->getPosition();

    const unsigned     row          = getGridRow(position.y, cellSize);
    const unsigned     col          = getGridColumn(position.x, cellSize);
    const sf::Vector2f cellPosition = getCellPosition(row, col, cellSize);

    building->setPosition(cellPosition);

    objects.push_back(std::move(building));
}

float Grid::getCellSize() const {
    return cellSize;
}