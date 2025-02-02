#pragma once

#include "SFML/Graphics/Color.hpp"
#include "SFML/System/Vector2.hpp"
#include <optional>

typedef enum BuildingType {
    TownHall,
    School,
    Farm,
    GoldMine,
    Quarry,
    LumberjackHouse,
    SawMill,
    Tower,
} BuildingType;

inline sf::Color getBuildingsColor(const BuildingType type) {
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

inline sf::Vector2i getBuildingsCells(const BuildingType type) {
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

inline std::optional<float> getBuildingsRange(const BuildingType type) {
    switch (type) {
        case Tower:
            return 6;
        default:
            return std::nullopt;
    }
}