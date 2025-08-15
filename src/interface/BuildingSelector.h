#pragma once

#include "../board/buildings/Building.h"
#include "SFML/Graphics/RectangleShape.hpp"
#include <span>

class BuildingSelector {

private:
    std::vector<BuildingType> buildings;
    std::vector<sf::RectangleShape> elements;
    float rightBorder = 0; // X position of the right corner of the farthest right element + space

public:
    BuildingSelector() = delete;
    BuildingSelector(std::initializer_list<BuildingType> inputElements);
    ~BuildingSelector() = default;

    void                                      draw() const;
    [[nodiscard]] std::optional<BuildingType> getSelected() const;
    void                                      scroll(float delta) const;
};
