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

void Game::handleEvent(const std::optional<sf::Event>& event) {
    using namespace Scene;

    const sf::Vector2i mousePosition = sf::Mouse::getPosition(Window::get());

    // Close window: exit
    if (event->is<sf::Event::Closed>()) Window::get().close();

    if (event->is<sf::Event::MouseButtonPressed>()) {
        if (isButtonPressed(sf::Mouse::Button::Left)) {
            if (Window::isMouseOnMainView(mousePosition)) {
                constexpr float radius     = 10;
                constexpr float ringRadius = 100;

                sf::CircleShape shape(radius);
                shape.setPosition({static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y)});
                shape.setFillColor(selectedBuilding.value_or(sf::Color::Transparent));

                sf::CircleShape ring(ringRadius);
                ring.setPosition({static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y)});
                ring.setFillColor(sf::Color::Transparent);
                ring.setOutlineThickness(2.f);
                ring.setOutlineColor(sf::Color::Red);

                grid.addObject(std::make_unique<sf::CircleShape>(shape));
                grid.addObject(std::make_unique<sf::CircleShape>(ring));
            }

            if (Window::isMouseOnBottomView(mousePosition)) {
                if (const std::optional<sf::Color> selected = buildingSelector.getSelected()) {
                    selectedBuilding = selected;
                }
            }
        }
    }

    if (const auto e = event->getIf<sf::Event::MouseWheelScrolled>()) {
        if (Window::isMouseOnBottomView(mousePosition) && e->wheel == sf::Mouse::Wheel::Vertical) {
            buildingSelector.scroll(e->delta);
        }
    }
}

void Game::draw() {
    using namespace Scene;

    // Clear screen
    Window::get().clear();

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
    grid            = Grid(32, 32, width / 32);

    std::array colors = {sf::Color::Red, sf::Color::Green, sf::Color::Blue, sf::Color::Yellow, sf::Color::Cyan};
    buildingSelector  = BuildingSelector(colors);
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
            handleEvent(event);
        }

        draw();
    }
}