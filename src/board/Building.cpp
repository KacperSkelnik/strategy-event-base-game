//
// Created by Kacper Skelnik on 01.02.2025.
//

#include "Building.h"

#include "../globals/Scene.h"
#include "../globals/Settings.h"

Building::Building(const BuildingType type, GridPosition position): type(type), isSelected(true), position(position) {
    using namespace Settings;

    rect.setFillColor(getBuildingsColor(type));

    if (getBuildingsRange(type)) {
        range.emplace(sf::CircleShape {});
        range->setFillColor(sf::Color::Transparent);
        range->setOutlineThickness(2.f);
        range->setOutlineColor(sf::Color::Red);
    }

    recalculatePosition();
    recalculateSize();
}

void Building::recalculatePosition() {
    using namespace Settings;

    const auto [row, column] = position;
    const float cellSize     = Variables::getCellSize();

    const float x = column * cellSize;
    const float y = row * cellSize;
    rect.setPosition({x, y});

    if (const std::optional<float> maybeRange = getBuildingsRange(type)) {
        const float radius         = maybeRange.value() * Variables::getCellSize();
        const auto [width, height] = getBuildingsCells(type);

        const float offsetX = -radius + width * cellSize / 2;
        const float offsetY = -radius + height * cellSize / 2;
        range->setPosition({x + offsetX, y + offsetY});
    }
}

void Building::recalculateSize() {
    using namespace Settings;

    const float cellSize       = Variables::getCellSize();
    const auto [width, height] = getBuildingsCells(type);

    rect.setSize({width * cellSize, height * cellSize});

    if (const std::optional<float> maybeRange = getBuildingsRange(type)) {
        const float radius = maybeRange.value() * cellSize;
        range->setRadius(radius);
    }
}

void Building::drawBuilding() const {
    using namespace Scene;

    Window::mainViewFocus();
    Window::get().draw(rect);
}

void Building::drawRange() const {
    using namespace Scene;

    if (range) {
        Window::mainViewFocus();
        Window::get().draw(range.value());
    }
}

void Building::draw() const {
    drawBuilding();
    if (isSelected) {
        drawRange();
    }
}