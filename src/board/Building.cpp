//
// Created by Kacper Skelnik on 01.02.2025.
//

#include "Building.h"

#include "../globals/Scene.h"
#include "../globals/Settings.h"

sf::Color Building::getColor(const BuildingType type) {
    switch (type) {
        case TownHall:
            return sf::Color::Red;
        case School:
            return sf::Color::Blue;
        case Farm:
            return sf::Color::Green;
        case GoldMine:
            return sf::Color::Yellow;
        case Quarry:
            return sf::Color::Cyan;
        case LumberjackHouse:
            return sf::Color::Magenta;
        case SawMill:
            return sf::Color::White;
        case Tower:
            return sf::Color::Black;
        default:
            return sf::Color::Transparent;
    }
}

sf::Vector2i Building::getCells(const BuildingType type) {
    switch (type) {
        case TownHall:
        case School:
            return {3, 3};
        case Farm:
            return {4, 4};
        case GoldMine:
        case Quarry:
        case SawMill:
            return {2, 2};
        case LumberjackHouse:
        case Tower:
            return {1, 1};
        default:
            return {0, 0};
    }
}

std::optional<float> getRange(const BuildingType type) {
    switch (type) {
        case Tower:
            return 6;
        default:
            return std::nullopt;
    }
}

Building::Building(const BuildingType type, const sf::Vector2f& size, const sf::Vector2f& position):
    type(type), isSelected(true) {
    using namespace Settings;

    // RECT
    rect.setPosition(position);
    rect.setSize(size);
    rect.setFillColor(getColor(type));

    // RANGE
    if (const std::optional<float> maybeRange = getRange(type)) {
        const auto [x, y]  = position;
        const float radius = maybeRange.value() * Variables::getCellSize();

        range.emplace(sf::CircleShape {});

        range->setPosition({x - radius + size.x / 2, y - radius + size.y / 2});
        range->setRadius(radius);

        range->setFillColor(sf::Color::Transparent);

        range->setOutlineThickness(2.f);
        range->setOutlineColor(sf::Color::Red);
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