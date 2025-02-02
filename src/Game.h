#pragma once

#include "interface/BuildingSelector.h"
#include "interface/Grid.h"
#include <vector>

class Game {
  private:
    Grid                                   grid;
    BuildingSelector                       buildingSelector;
    std::optional<BuildingType>            selectedBuilding;
    std::vector<std::unique_ptr<Building>> buildings;

    static void onClose();
    void        onMousePress(const sf::Event::MouseButtonPressed* event);
    void        onMouseScroll(const sf::Event::MouseWheelScrolled* event);

    void handleEvent(const sf::Event& event);
    void draw();

  public:
    Game();
    ~Game();
    void run();
};