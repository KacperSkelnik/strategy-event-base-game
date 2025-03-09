#pragma once
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/System/Vector2.hpp"
#include <array>

class EconomyCell {
  private:
    const long&          economyResourceReference;
    std::array<long, 50> amountPlot;
    size_t               amountPlotHead;

    sf::RectangleShape background;

    void addNewAmount();

  public:
    EconomyCell() = delete;
    explicit EconomyCell(const long& economyResourceReference, sf::Vector2f position, sf::Vector2f size);
    ~EconomyCell() = default;

    void draw();
};