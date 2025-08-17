#pragma once

#include "UserInput.h"
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
    std::shared_ptr<EconomyState> economyState;

    // Interface
    std::shared_ptr<BuildingSelector> buildingSelector;
    EconomyPanel                      economyPanel;

    // Events
    std::shared_ptr<EventQueue>          eventQueue;
    std::shared_ptr<ScheduledEventQueue> scheduledEventQueue;
    EventLoop                            eventLoop;

    // Input
    UserInput userInput;

    void draw() const;

public:
    Game() = delete;
    explicit Game(std::initializer_list<BuildingType> buildingTypes);
    ~Game();

    static Game create(std::initializer_list<BuildingType> buildingTypes);
    void        run();
};