#pragma once
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/Text.hpp"
#include "SFML/System/Vector2.hpp"
#include <array>
#include <functional>

class EconomyCell {
  private:
    std::function<long()> economyResourceGetter;
    std::array<long, 250> values;
    sf::RectangleShape    background;
    sf::VertexArray       plot;
    float                 maxPlotValue;
    sf::Text              textRepresentation;

    void  updateValues();
    float calculateY(float value) const;
    void  updatePlot();

  public:
    EconomyCell() = delete;
    explicit EconomyCell(std::function<long()> economyResourceGetter, sf::Vector2f position, sf::Vector2f size);
    ~EconomyCell() = default;

    void update();
    void draw() const;
};