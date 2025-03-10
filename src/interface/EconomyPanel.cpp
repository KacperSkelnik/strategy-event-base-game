//
// Created by Kacper Skelnik on 11.02.2025.
//
#include "EconomyPanel.h"

#include "../globals/Resource.h"
#include "../globals/Screen.h"

EconomyPanel::EconomyPanel(const EconomyState& economyState): economyState(economyState) {
    using namespace Screen;
    using namespace Resource;

    const auto [centerX, centerY] = Window::getRightView().getCenter();
    const auto [width, height]    = Window::getRightView().getSize();
    const float basePositionX     = centerX - width / 2;
    const float basePositionY     = centerY - height / 2;

    const float space         = 0.05f * width;
    const float elementHeight = 0.05f * height;
    const float elementWidth  = width - 2 * space;

    elements.emplace_back(
        "Gold",
        [&]() {
            return economyState.getGold();
        },
        sf::Vector2f {basePositionX + space, basePositionY + space},
        sf::Vector2f {elementWidth, elementHeight}
    );
}

void EconomyPanel::update() {
    for (EconomyCell& element : elements) {
        element.update();
    }
}

void EconomyPanel::draw() const {

    for (const EconomyCell& element : elements) {
        element.draw();
    }
}