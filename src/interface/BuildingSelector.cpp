//
// Created by Kacper Skelnik on 25.01.2025.
//

#include "BuildingSelector.h"

#include "../globals/Scene.h"
#include "SFML/Graphics/RectangleShape.hpp"
#include <iostream>

BuildingSelector::BuildingSelector(const std::span<sf::Color>& inputElements) {
    using namespace Scene;

    const auto [centerX, centerY] = Window::getBottomView().getCenter();
    const auto [width, height]    = Window::getBottomView().getSize();
    const float basePositionX     = centerX - width / 2;
    const float basePositionY     = centerY - height / 2;

    const float elementSize = 0.7f * height;
    const float space       = 0.15f * height;

    elements.reserve(inputElements.size());
    float shift = space;
    for (const sf::Color color : inputElements) {
        sf::RectangleShape rect;
        rect.setSize({elementSize, elementSize});
        rect.setFillColor(color);
        rect.setPosition({basePositionX + shift, basePositionY + space});
        elements.emplace_back(rect);
        shift += (elementSize + space);
    }
    rightBorder = shift;
}

void BuildingSelector::draw() const {
    using namespace Scene;

    Window::bottomViewFocus();
    for (const sf::RectangleShape& element : elements) {
        Window::get().draw(element);
    }
}

std::optional<sf::Color> BuildingSelector::getSelected() const {
    using namespace Scene;

    const sf::Vector2i mousePosition = sf::Mouse::getPosition(Window::get());
    const sf::Vector2f worldPosition = Window::get().mapPixelToCoords(mousePosition);

    for (const sf::RectangleShape& element : elements) {
        if (element.getGlobalBounds().contains(worldPosition)) {
            return element.getFillColor();
        }
    }
    return std::nullopt;
}

void BuildingSelector::scroll(const float delta) const {
    using namespace Scene;

    const float offset  = -4 * delta;
    const float centerX = Window::getBottomView().getCenter().x;
    const float width   = Window::getBottomView().getSize().x;

    if (centerX - width / 2 + offset > 0 && centerX + width / 2 + offset < rightBorder) {
        Window::getBottomView().move({offset, 0});
    } else if (centerX - width / 2 + offset < 0) {
        Window::getBottomView().move({-(centerX - width / 2), 0});
    } else if (centerX + width / 2 + offset > rightBorder) {
        Window::getBottomView().move({rightBorder - (centerX + width / 2), 0});
    }
}