//
// Created by Kacper Skelnik on 25.01.2025.
//

#include "BuildingSelector.h"

#include "../globals/Screen.h"
#include "SFML/Graphics/RectangleShape.hpp"
#include <ranges>

BuildingSelector::BuildingSelector(const std::initializer_list<BuildingType> inputElements) {
    using namespace Screen;

    const auto  [centerX, centerY] = Window::getBottomView().getCenter();
    const auto  [width, height]    = Window::getBottomView().getSize();
    const float basePositionX      = centerX - width / 2;
    const float basePositionY      = centerY - height / 2;

    const float elementSize = 0.7f * height;
    const float space       = 0.15f * height;

    elements.reserve(inputElements.size() + 1); // +1 for the road
    buildings.reserve(inputElements.size() + 1);
    float shift = space;

    // roads
    {
        sf::RectangleShape rect;
        rect.setSize({elementSize, elementSize});
        rect.setTexture(&getBuildingTexture(RoadBuilding));
        rect.setPosition({basePositionX + shift, basePositionY + space});
        elements.emplace_back(rect);
        buildings.emplace_back(RoadBuilding);
        shift += (elementSize + space);
    }
    // others
    for (const BuildingType building : inputElements) {
        sf::RectangleShape rect;
        rect.setSize({elementSize, elementSize});
        rect.setTexture(&getBuildingTexture(building));
        rect.setPosition({basePositionX + shift, basePositionY + space});

        elements.emplace_back(rect);
        buildings.emplace_back(building);

        shift += (elementSize + space);
    }
    rightBorder = shift;
}

void BuildingSelector::draw() const {
    using namespace Screen;

    Window::bottomViewFocus();
    for (const sf::RectangleShape& element : elements) {
        Window::get().draw(element);
    }
}

std::optional<BuildingType> BuildingSelector::getSelected() const {
    using namespace Screen;

    Window::bottomViewFocus();

    const sf::Vector2i mousePosition = sf::Mouse::getPosition(Window::get());
    const sf::Vector2f worldPosition = Window::get().mapPixelToCoords(mousePosition);

    for (size_t i = 0; i < elements.size(); ++i) {
        if (elements[i].getGlobalBounds().contains(worldPosition) && i < buildings.size()) {
            return buildings[i];
        }
    }
    return std::nullopt;
}

void BuildingSelector::scroll(const float delta) const {
    using namespace Screen;

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