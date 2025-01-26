//
// Created by Kacper Skelnik on 25.01.2025.
//

#ifndef GAME_H
#define GAME_H
#include "interface/BuildingSelector.h"
#include "interface/Grid.h"

class Game {
  private:
    Grid                     grid;
    BuildingSelector         buildingSelector;
    std::optional<sf::Color> selectedBuilding;

    void handleEvent(const std::optional<sf::Event>& event);
    void draw();

  public:
    Game();
    ~Game();
    void run();
};

#endif // GAME_H
