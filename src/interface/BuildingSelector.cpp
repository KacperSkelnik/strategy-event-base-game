//
// Created by Kacper Skelnik on 25.01.2025.
//

#include "BuildingSelector.h"

#include "../globals/Scene.h"
#include "SFML/Graphics/RectangleShape.hpp"

void BuildingSelector::draw() {
    using namespace Scene;

    const auto [centerX, centerY] = Window::getBottomView().getCenter();
    const auto [width, height]    = Window::getBottomView().getSize();
    const float basePositionX     = centerX - width / 2;
    const float basePositionY     = centerY - height / 2;

    sf::RectangleShape green;
    green.setSize({100, 100});
    green.setFillColor(sf::Color::Green);
    green.setPosition({basePositionX + 50, basePositionY + 50});

    sf::RectangleShape red;
    red.setSize({100, 100});
    red.setFillColor(sf::Color::Red);
    red.setPosition({basePositionX + 250, basePositionY + 50});

    sf::RectangleShape yellow;
    yellow.setSize({100, 100});
    yellow.setFillColor(sf::Color::Yellow);
    yellow.setPosition({basePositionX + 450, basePositionY + 50});

    sf::RectangleShape white;
    white.setSize({100, 100});
    white.setFillColor(sf::Color::White);
    white.setPosition({basePositionX + 650, basePositionY + 50});

    Window::bottomViewFocus();
    Window::get().draw(green);
    Window::get().draw(red);
    Window::get().draw(yellow);
    Window::get().draw(white);
}