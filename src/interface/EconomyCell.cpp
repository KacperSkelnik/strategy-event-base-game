//
// Created by Kacper Skelnik on 11.02.2025.
//

#include "EconomyCell.h"

#include "../globals/Screen.h"
#include "SFML/Graphics/RectangleShape.hpp"

EconomyCell::EconomyCell(const long& economyResourceReference, const sf::Vector2f position, const sf::Vector2f size):
    economyResourceReference(economyResourceReference), amountPlot {}, amountPlotHead(0) {

    background = sf::RectangleShape();
    background.setSize(size);
    background.setPosition(position);
}

void EconomyCell::addNewAmount() {
    amountPlot[amountPlotHead] = economyResourceReference;
    amountPlotHead             = (amountPlotHead + 1) % amountPlot.size();
}

void EconomyCell::draw() {
    using namespace Screen;

    addNewAmount();

    Window::rightViewFocus();
    Window::get().draw(background);
}