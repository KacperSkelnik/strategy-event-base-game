//
// Created by Kacper Skelnik on 25.01.2025.
//

#ifndef BUILDING_SELECTOR_H
#define BUILDING_SELECTOR_H
#include "SFML/Graphics/Color.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include <span>

class BuildingSelector {
  private:
    std::vector<sf::RectangleShape> elements;
    float rightBorder = 0; // X position of the right corner of the farthest right element + space

  public:
    BuildingSelector() = default;
    explicit BuildingSelector(const std::span<sf::Color>& inputElements);
    ~BuildingSelector() = default;
    void                                   draw() const;
    [[nodiscard]] std::optional<sf::Color> getSelected() const;
    void                                   scroll(float delta) const;
};

#endif // BUILDING_SELECTOR_H
