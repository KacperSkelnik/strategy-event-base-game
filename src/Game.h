#pragma once

#include "board/Board.h"
#include "board/Grid.h"
#include "economy/EconomyState.h"
#include "events/EventLoop.h"
#include "events/EventQueue.h"
#include "interface/BuildingSelector.h"
#include "interface/EconomyPanel.h"

class Game {
  private:
    // Board
    std::shared_ptr<Grid>  grid;
    std::shared_ptr<Board> board;

    // State
    std::optional<BuildingType>   selectedBuilding;
    std::shared_ptr<EconomyState> economyState;

    // Interface
    BuildingSelector buildingSelector;
    EconomyPanel     economyPanel;
    bool             screenCanBeDragged;

    // Events
    std::shared_ptr<EventQueue> eventQueue;
    EventLoop                   eventLoop;

    static void onClose();
    void        onMousePress(const sf::Event::MouseButtonPressed* event);
    void        onMouseRelease(const sf::Event::MouseButtonReleased* event);
    void        onMouseScroll(const sf::Event::MouseWheelScrolled* event) const;

    void handleEvent(const sf::Event& event);
    void draw() const;
    void runEventLoop() const;

    Game(std::initializer_list<BuildingType> buildingTypes);

  public:
    Game() = delete;
    ~Game();
    static Game create(std::initializer_list<BuildingType> buildingTypes);
    void        run();
};