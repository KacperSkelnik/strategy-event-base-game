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

    const float elementSize = 0.2f * width;
    const float space       = 0.05f * width;

    float shift = space;
    elements.emplace_back(EconomyCell(economyState.getGold(), {elementSize, elementSize}, {basePositionX + space, basePositionY + shift}));
    shift += (elementSize + space);
}

void EconomyPanel::draw() const {

    for (EconomyCell element : elements) {
        element.draw();
    }
}