#pragma once

#include "interface/BuildingSelector.h"
#include "interface/Grid.h"

class Game {
  private:
    Grid                        grid;
    BuildingSelector            buildingSelector;
    std::optional<BuildingType> selectedBuilding;

    static void onClose();
    void        onMousePress(const sf::Event::MouseButtonPressed* event);
    void        onMouseScroll(const sf::Event::MouseWheelScrolled* event) const;

    void handleEvent(const sf::Event& event);
    void draw();

  public:
    Game();
    ~Game();
    void run();
};