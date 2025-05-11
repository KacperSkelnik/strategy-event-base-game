//
// Created by Kacper Skelnik on 25.01.2025.
//

#include "Game.h"

#include "board/events/CreateBuildingHandler.h"
#include "board/Grid.h"
#include "globals/Resource.h"
#include "globals/Screen.h"
#include "globals/Settings.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

Game::Game(const std::initializer_list<BuildingType> buildingTypes):
    grid(std::make_shared<Grid>(32, 32)),
    board(std::make_shared<Board>(grid)),
    economyState(EconomyState(500)),
    buildingSelector(BuildingSelector(buildingTypes)),
    economyPanel(economyState),
    screenCanBeDragged(false),
    eventQueue(std::make_shared<EventQueue>()),
    eventLoop(EventLoop(eventQueue)) {}

Game Game::create(const std::initializer_list<BuildingType> buildingTypes) {
    using namespace Settings;
    using namespace Screen;
    using namespace Resource;

    Variables::init();
    Window::init(Variables::getWindowWidth(), Variables::getWindowHeight());
    Fonts::init();
    Textures::init();

    return {buildingTypes};
}

Game::~Game() {
    using namespace Settings;
    using namespace Screen;
    using namespace Resource;

    Variables::shutDown();
    Window::shutDown();
    Fonts::shutDown();
    Textures::shutDown();
}

void Game::onClose() {
    using namespace Screen;

    Window::get().close();
}

void Game::onMousePress(const sf::Event::MouseButtonPressed* event) {
    using namespace Screen;

    if (event->button == sf::Mouse::Button::Left) {
        if (Window::isMouseOnMainView(event->position)) {
            if (selectedBuilding) {
                const auto handler = std::make_shared<CreateBuildingHandler>(selectedBuilding.value(), event->position);
                const auto _event  = std::make_shared<Event>(board, handler);
                eventQueue->push(_event);
            }
        }

        if (Window::isMouseOnBottomView(event->position)) {
            if (const std::optional<BuildingType> selected = buildingSelector.getSelected()) {
                selectedBuilding = selected;
            }
        }
    }

    if (event->button == sf::Mouse::Button::Right) {
        selectedBuilding = std::nullopt;
    }

    if (event->button == sf::Mouse::Button::Middle) {
        screenCanBeDragged = true;
    }
}

void Game::onMouseRelease(const sf::Event::MouseButtonReleased* event) {
    using namespace Screen;

    if (event->button == sf::Mouse::Button::Middle) {
        screenCanBeDragged = false;
        Window::resetDraggingViewManualMousePosition();
    }
}

void Game::onMouseScroll(const sf::Event::MouseWheelScrolled* event) const {
    using namespace Screen;
    using namespace Settings;

    if (Window::isMouseOnBottomView(event->position) && event->wheel == sf::Mouse::Wheel::Vertical) {
        buildingSelector.scroll(event->delta);
    }
    if (Window::isMouseOnMainView(event->position) && event->wheel == sf::Mouse::Wheel::Vertical) {
        if (event->delta > 0 && Window::getZoomsCnt() <= Variables::getMaxZoomsCnt()) {
            Window::getMainView().zoom(1 - Variables::getZoomFactor());
            Window::increaseZoomsCnt();
        }
        if (event->delta < 0 && Window::getZoomsCnt() >= Variables::getMinZoomsCnt()) {
            Window::getMainView().zoom(1 + Variables::getZoomFactor());
            Window::decreaseZoomsCnt();
        }
    }
}

void Game::handleEvent(const sf::Event& event) {
    using namespace Screen;

    // Close window: exit
    if (event.is<sf::Event::Closed>()) {
        onClose();
    }
    if (const auto e = event.getIf<sf::Event::MouseButtonPressed>()) {
        onMousePress(e);
    }
    if (const auto e = event.getIf<sf::Event::MouseButtonReleased>()) {
        onMouseRelease(e);
    }
    if (const auto e = event.getIf<sf::Event::MouseWheelScrolled>()) {
        onMouseScroll(e);
    }
}

void Game::draw() const {
    using namespace Screen;

    // Clear screen
    Window::get().clear(sf::Color::White);

    grid->draw(selectedBuilding);
    buildingSelector.draw();
    economyPanel.draw();

    // Update the window
    Window::get().display();
}

void Game::run() {
    using namespace Screen;
    using namespace Resource;

    sf::Text text(Fonts::getRegular());
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);

    // Start the game loop
    while (Window::get().isOpen()) {
        eventLoop.run();

        while (const std::optional event = Window::get().pollEvent()) {
            handleEvent(event.value());
        }

        Window::dragMainView(); // screen dragging after the mouse
        Window::dragMainViewManually(screenCanBeDragged);
        economyPanel.update();

        draw();
    }
}