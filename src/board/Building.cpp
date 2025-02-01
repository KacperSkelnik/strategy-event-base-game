//
// Created by Kacper Skelnik on 01.02.2025.
//

#include "Building.h"

#include "../globals/Scene.h"

inline sf::Color Building::getColor(const BuildingType type) {
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

inline sf::Vector2f getSize(const BuildingType type) {
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

inline std::optional<float> getRange(const BuildingType type) {
    switch (type) {
        case Tower:
            return 6;
        default:
            return std::nullopt;
    }
}

Building::Building(const BuildingType type, const float cellSize, sf::Vector2i mousePosition):
    type(type), isSelected(true) {

    auto [x, y] = mousePosition;
    // RECT
    rect.setPosition({static_cast<float>(x), static_cast<float>(y)});

    auto [xDim, yDim] = getSize(type);
    rect.setSize({cellSize * xDim, cellSize * yDim});

    rect.setFillColor(getColor(type));

    // RANGE
    if (std::optional<float> maybeRange = getRange(type)) {
        range.emplace(sf::CircleShape {});
        range->setPosition({static_cast<float>(x), static_cast<float>(y)});

        range->setRadius(maybeRange.value() * cellSize);

        range->setFillColor(sf::Color::Transparent);

        range->setOutlineThickness(2.f);
        range->setOutlineColor(sf::Color::Red);
    }
}

void Building::drawBuilding() const {
    using namespace Scene;

    Window::get().draw(rect);
}

void Building::drawRange() const {
    using namespace Scene;

    if (range) {
        Window::get().draw(range.value());
    }
}

sf::Vector2f Building::getPosition() const {
    return rect.getPosition();
}

void Building::setPosition(const sf::Vector2f position) {
    rect.setPosition(position);
    if (range) {
        auto [width, height] = rect.getSize();
        auto [x, y]          = position;
        range->setPosition({x - range->getRadius() + width / 2, y - range->getRadius() + height / 2});
    }
}

void Building::draw() const {
    drawBuilding();
    if (isSelected) {
        drawRange();
    }
}