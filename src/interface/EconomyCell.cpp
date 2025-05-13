//
// Created by Kacper Skelnik on 11.02.2025.
//

#include "EconomyCell.h"

#include "../globals/Resource.h"
#include "../globals/Screen.h"
#include "SFML/Graphics/RectangleShape.hpp"

EconomyCell::EconomyCell(std::string economyName, std::function<int()> economyResourceGetter, const sf::Vector2f position, const sf::Vector2f size):
    economyResourceGetter(std::move(economyResourceGetter)),
    values {},
    plot(sf::PrimitiveType::LineStrip, values.size()),
    maxPlotValue(0),
    textRepresentation(Resource::Fonts::getRegular()),
    economyName(std::move(economyName)) {
    using namespace Resource;

    // Frame
    background = sf::RectangleShape();
    background.setSize(size);
    background.setPosition(position);
    background.setOutlineColor(sf::Color::Black);
    background.setOutlineThickness(2);

    // Text
    textRepresentation.setCharacterSize(24);
    textRepresentation.setString(economyName + ": 0");
    textRepresentation.setFillColor(sf::Color::Black);
    textRepresentation.setPosition(
        {position.x + size.x / 2, position.y + size.y / 2 + textRepresentation.getGlobalBounds().size.y / 2}
    );

    // Plot
    values.fill(economyResourceGetter());
    maxPlotValue = static_cast<float>(2 * economyResourceGetter());

    const float plotStep = background.getSize().x / static_cast<float>(plot.getVertexCount());
    for (size_t i = 0; i < plot.getVertexCount(); ++i) {
        const float x    = background.getPosition().x + static_cast<float>(i) * plotStep;
        const float y    = calculateY(static_cast<float>(values[i]));
        plot[i].position = sf::Vector2f(x, y);
        plot[i].color    = sf::Color::Green;
    }
}

void EconomyCell::updateValues() {
    if (values.back() != economyResourceGetter()) {
        std::move(values.begin() + 1, values.end(), values.begin());
        values.back() = economyResourceGetter();
    }
}

float EconomyCell::calculateY(const float value) const {
    return background.getPosition().y + background.getSize().y - value / maxPlotValue * background.getSize().y;
}

void EconomyCell::updatePlot() {
    const auto newValue = static_cast<float>(economyResourceGetter());
    if (newValue > maxPlotValue) {
        maxPlotValue = newValue;
    }
    for (size_t i = 0; i < plot.getVertexCount(); ++i) {
        plot[i].position.y = calculateY(static_cast<float>(values[i]));
    }
}

void EconomyCell::updateText() {
    textRepresentation.setString(economyName + ": " + std::to_string(economyResourceGetter()));
    textRepresentation.setOrigin(
        {textRepresentation.getLocalBounds().size.x / 2, textRepresentation.getLocalBounds().size.y / 2}
    );
}

void EconomyCell::update() {
    updateValues();
    updatePlot();
    updateText();
}

void EconomyCell::draw() const {
    using namespace Screen;

    Window::rightViewFocus();
    Window::get().draw(background);
    Window::get().draw(plot);
    Window::get().draw(textRepresentation);
}