//
// Created by Kacper Skelnik on 25.01.2025.
//

#include "Game.h"

#include "globals/Resource.h"
#include "globals/Scene.h"
#include "interface/Grid.h"
#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

void Game::onClose() {
    using namespace Scene;

    Window::get().close();
}

void Game::onMousePress(const sf::Event::MouseButtonPressed* event) {
    using namespace Scene;

    std::cout << event->position.x << " " << event->position.y << std::endl;

    if (event->button == sf::Mouse::Button::Left) {
        if (Window::isMouseOnMainView(event->position)) {
            if (selectedBuilding) {
                Building building(selectedBuilding.value(), grid.getCellSize(), event->position);
                grid.addBuilding(std::make_unique<Building>(building));
            }
        }

        if (Window::isMouseOnBottomView(event->position)) {
            if (const std::optional<BuildingType> selected = buildingSelector.getSelected()) {
                selectedBuilding = selected;
            }
        }
    }
}

void Game::onMouseScroll(const sf::Event::MouseWheelScrolled* event) const {
    using namespace Scene;

    if (Window::isMouseOnBottomView(event->position) && event->wheel == sf::Mouse::Wheel::Vertical) {
        buildingSelector.scroll(event->delta);
    }
}

void Game::handleEvent(const sf::Event& event) {
    using namespace Scene;

    // Close window: exit
    if (event.is<sf::Event::Closed>()) {
        onClose();
    }
    if (const auto e = event.getIf<sf::Event::MouseButtonPressed>()) {
        onMousePress(e);
    }
    if (const auto e = event.getIf<sf::Event::MouseWheelScrolled>()) {
        onMouseScroll(e);
    }
}

void Game::draw() {
    using namespace Scene;

    // Clear screen
    Window::get().clear(sf::Color::White);

    grid.draw();
    buildingSelector.draw();

    // Update the window
    Window::get().display();
}

Game::Game() {
    using namespace Scene;
    using namespace Resource;

    Window::init(800, 1000);
    Fonts::init();

    auto [width, _] = Window::getMainView().getSize();
    grid            = Grid(64, 64, width / 64);

    std::array buildings = {
        TownHall,
        School,
        Farm,
        GoldMine,
        Quarry,
        LumberjackHouse,
        SawMill,
        Tower,
    };
    buildingSelector = BuildingSelector(buildings);
}

Game::~Game() {
    using namespace Scene;
    using namespace Resource;

    Fonts::shutDown();
    Window::shutDown();
}

void Game::run() {
    using namespace Scene;
    using namespace Resource;

    sf::Text text(Fonts::getRegular());
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);

    // Start the game loop
    while (Window::get().isOpen()) {
        while (const std::optional event = Window::get().pollEvent()) {
            handleEvent(event.value());
        }
        draw();
    }
}