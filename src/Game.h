#pragma once

#include "interface/BuildingSelector.h"
#include "interface/Grid.h"
#include <vector>

class Game {
  private:
    // Interface
    Grid             grid;
    BuildingSelector buildingSelector;
    bool             screenCanBeDragged;

    // Board
    std::vector<std::unique_ptr<Building>> buildings;

    // State
    std::optional<BuildingType> selectedBuilding;

    static void onClose();
    void        onMousePress(const sf::Event::MouseButtonPressed* event);
    void        onMouseRelease(const sf::Event::MouseButtonReleased* event);
    void        onMouseScroll(const sf::Event::MouseWheelScrolled* event) const;

    void handleEvent(const sf::Event& event);
    void draw() const;

  public:
    Game();
    ~Game();
    void run();
};