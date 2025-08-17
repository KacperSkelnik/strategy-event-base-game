//
// Created by Kacper Skelnik on 17.08.2025.
//

#include "UserInput.h"

#include "events/Event.h"
#include "events/EventParams.h"
#include "globals/Screen.h"
#include "globals/Settings.h"

UserInput::UserInput(const std::shared_ptr<Board>&            board,
                     const std::shared_ptr<EventQueue>&       eventQueue,
                     const std::shared_ptr<BuildingSelector>& buildingSelector): board(board),
    eventQueue(eventQueue),
    buildingSelector(buildingSelector),
    screenCanBeDragged(false) {
}

void UserInput::onClose() {
    using namespace Screen;

    Window::get().close();
}

void UserInput::onMousePress(const sf::Event::MouseButtonPressed* event) {
    using namespace Screen;

    if (event->button == sf::Mouse::Button::Left) {
        if (Window::isMouseOnMainView(event->position)) {
            if (selectedBuilding) {
                const auto params = CreateBuildingParams{selectedBuilding.value(), event->position};
                eventQueue->push(std::make_shared<Event>(board, CreateBuilding, params));
            } else if (const auto building = board->trySelectBuilding(event->position); building.has_value()) {
                switch (building.value()->getType()) {
                    case School: {
                        const auto params = CreateCharacterParams{Serf, building.value()};
                        eventQueue->push(std::make_shared<Event>(board, CreateCharacter, params));
                        break;
                    }
                    default: {
                        break;
                    }
                }
            }
        }

        if (Window::isMouseOnBottomView(event->position)) {
            if (const std::optional<BuildingType> selected = buildingSelector->getSelected()) {
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

void UserInput::onMouseRelease(const sf::Event::MouseButtonReleased* event) {
    using namespace Screen;

    if (event->button == sf::Mouse::Button::Middle) {
        screenCanBeDragged = false;
        Window::resetDraggingViewManualMousePosition();
    }
}

void UserInput::onMouseScroll(const sf::Event::MouseWheelScrolled* event) const {
    using namespace Screen;
    using namespace Settings;

    if (Window::isMouseOnBottomView(event->position) && event->wheel == sf::Mouse::Wheel::Vertical) {
        buildingSelector->scroll(event->delta);
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

void UserInput::handleEvent() {
    using namespace Screen;

    const std::optional event = Window::get().pollEvent();
    if (event.has_value()) {
        // Close window: exit
        if (event->is<sf::Event::Closed>()) {
            onClose();
        }
        if (const auto e = event->getIf<sf::Event::MouseButtonPressed>()) {
            onMousePress(e);
        }
        if (const auto e = event->getIf<sf::Event::MouseButtonReleased>()) {
            onMouseRelease(e);
        }
        if (const auto e = event->getIf<sf::Event::MouseWheelScrolled>()) {
            onMouseScroll(e);
        }
    }

    Window::dragMainView();
    Window::dragMainViewManually(screenCanBeDragged);
}