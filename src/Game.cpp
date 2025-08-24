//
// Created by Kacper Skelnik on 25.01.2025.
//

#include "Game.h"

#include "board/Grid.h"
#include "economy/events/SpendResourceHandler.h"
#include "globals/Random.h"
#include "globals/Resource.h"
#include "globals/Screen.h"
#include "globals/Settings.h"
#include "globals/Time.h"
#include <SFML/Graphics.hpp>

Game::Game(const std::initializer_list<BuildingType> buildingTypes, const GridState& initialState):
    grid(std::make_shared<Grid>(32, 32)),
    board(std::make_shared<Board>(grid)),
    economyState(std::make_shared<EconomyState>(500)),
    buildingSelector(std::make_shared<BuildingSelector>(buildingTypes)),
    economyPanel(EconomyPanel(economyState)),
    eventQueue(std::make_shared<EventQueue>()),
    scheduledEventQueue(std::make_shared<ScheduledEventQueue>()),
    eventLoop(EventLoop(eventQueue, scheduledEventQueue, economyState, board)),
    userInput(UserInput(board, eventQueue, buildingSelector)) {

    gridsBuffer = {std::make_unique<GridState>(initialState), std::make_unique<GridState>(initialState)};
}

Game Game::create(const std::initializer_list<BuildingType> buildingTypes) {
    using namespace Settings;
    using namespace Screen;
    using namespace Resource;
    using namespace Random;
    using namespace Time;

    Variables::init();
    Window::init(Variables::getWindowWidth(), Variables::getWindowHeight());
    Fonts::init();
    Textures::init();
    RandomGenerator::init();
    Clock::init();

    const auto initialState = GridState(32, 32);

    return Game{buildingTypes, initialState};
}

Game::~Game() {
    using namespace Settings;
    using namespace Screen;
    using namespace Resource;
    using namespace Random;
    using namespace Time;

    eventLoop.stop();

    Variables::shutDown();
    Window::shutDown();
    Fonts::shutDown();
    Textures::shutDown();
    RandomGenerator::shutDown();
    Clock::shutDown();
}

void Game::draw() const {
    using namespace Screen;

    // Clear screen
    Window::get().clear(sf::Color::White);

    grid->draw(userInput.getSelectedBuilding(), userInput.isRoadSelected());
    buildingSelector->draw();
    economyPanel.draw();

    // Update the window
    Window::get().display();
}

void Game::update() {
    eventLoop.drain();
    economyPanel.update();
    userInput.handleEvent();
}

void Game::run() {
    using namespace Screen;

    while (Window::get().isOpen()) {

        grid->setState(gridsBuffer[backIndex]);
        update();

        grid->setState(gridsBuffer[frontIndex]);
        draw();

        *gridsBuffer[frontIndex] = *gridsBuffer[backIndex];
    }
}