//
// Created by Kacper Skelnik on 25.01.2025.
//

#include "Screen.h"

#include "Settings.h"
#include <cassert>

namespace Screen {

    static Window* s_instance = nullptr;

    bool Window::isMouseOn(const sf::Vector2i& mousePosition, const sf::View& view) {
        const auto [xStart, yStart]                    = view.getViewport().position;
        const auto [windowWidth, windowHeight]         = get().getSize();
        const auto [widthProportion, heightProportion] = view.getViewport().size;
        const float width                              = widthProportion * static_cast<float>(windowWidth);
        const float height                             = heightProportion * static_cast<float>(windowHeight);

        const float x = static_cast<float>(windowWidth) * xStart;
        const float y = static_cast<float>(windowHeight) * yStart;

        if (x < static_cast<float>(mousePosition.x) && x + width > static_cast<float>(mousePosition.x) &&
            y < static_cast<float>(mousePosition.y) && y + height > static_cast<float>(mousePosition.y)) {
            return true;
        }
        return false;
    }

    void Window::init(const unsigned initialWidth, const unsigned initialHeight) {
        assert(!s_instance);

        const unsigned width  = initialWidth;
        const unsigned height = initialHeight;

        const float width_f = static_cast<float>(width);

        const float mainWindowHeight   = static_cast<float>(height) * 0.9f;
        const float bottomWindowHeight = static_cast<float>(height) * 0.1f;

        s_instance = new Window();

        s_instance->window = sf::RenderWindow(sf::VideoMode({width, height}), "Tower Defence");

        s_instance->mainView = sf::View(sf::FloatRect({0.f, 0.f}, {width_f, mainWindowHeight}));
        s_instance->mainView.setViewport(sf::FloatRect({0.f, 0.f}, {1, 0.9f}));

        s_instance->bottomView = sf::View(sf::FloatRect({0.f, mainWindowHeight}, {width_f, bottomWindowHeight}));
        s_instance->bottomView.setViewport(sf::FloatRect({0.f, 0.9}, {1, 0.1f}));

        s_instance->draggingViewClock.reset();
        s_instance->draggingViewClock.start();

        s_instance->draggingViewManualMousePosition = std::nullopt;

        s_instance->zoomsCnt = 0;
    }

    void Window::shutDown() {
        assert(s_instance);

        delete s_instance;

        s_instance = nullptr;
    }

    sf::RenderWindow& Window::get() {
        assert(s_instance);

        return s_instance->window;
    }

    sf::View& Window::getMainView() {
        assert(s_instance);

        return s_instance->mainView;
    }

    void Window::mainViewFocus() {
        assert(s_instance);

        s_instance->window.setView(s_instance->mainView);
    }

    bool Window::isMouseOnMainView(const sf::Vector2i& mousePosition) {
        assert(s_instance);

        return isMouseOn(mousePosition, s_instance->mainView);
    }

    sf::View& Window::getBottomView() {
        assert(s_instance);

        return s_instance->bottomView;
    }

    void Window::bottomViewFocus() {
        assert(s_instance);

        s_instance->window.setView(s_instance->bottomView);
    }

    bool Window::isMouseOnBottomView(const sf::Vector2i& mousePosition) {
        assert(s_instance);

        return isMouseOn(mousePosition, s_instance->bottomView);
    }

    void Window::dragMainView() {
        assert(s_instance);
        using namespace Settings;

        auto move = [](const sf::Vector2f offset, const bool canMove) {
            if (canMove) {
                mainViewFocus();
                getMainView().move(offset);
            }
        };

        const auto [x, y] = sf::Mouse::getPosition(s_instance->window);

        const float draggingPart                   = Variables::getViewDraggingPart();
        const auto [viewportWidth, viewportHeight] = s_instance->mainView.getViewport().size;
        const float viewWidth                      = viewportWidth * static_cast<float>(Variables::getWindowWidth());
        const float viewHeight                     = viewportHeight * static_cast<float>(Variables::getWindowHeight());
        const float draggingWidth                  = draggingPart * viewWidth;
        const float draggingHeight                 = draggingPart * viewHeight;

        bool moved   = false;
        bool canMove = false;
        if (s_instance->draggingViewClock.getElapsedTime() >= Variables::getViewDraggingTime()) {
            canMove = true;
        }

        if (static_cast<float>(x) < draggingWidth && static_cast<float>(y) > 0) {
            move({-Variables::getViewDraggingOffset(), 0}, canMove);
            moved = true;
        }
        if (static_cast<float>(x) > viewWidth - draggingWidth) {
            move({Variables::getViewDraggingOffset(), 0}, canMove);
            moved = true;
        }
        if (static_cast<float>(y) < draggingHeight && static_cast<float>(y) > 0) {
            move({0, -Variables::getViewDraggingOffset()}, canMove);
            moved = true;
        }
        if (static_cast<float>(y) > viewHeight - draggingHeight && static_cast<float>(y) < viewHeight) {
            move({0, Variables::getViewDraggingOffset()}, canMove);
            moved = true;
        }

        if (!moved) {
            s_instance->draggingViewClock.restart();
        }
    }

    void Window::dragMainViewManually(const bool screenCanBeDragged) {
        assert(s_instance);

        if (screenCanBeDragged) {
            if (s_instance->draggingViewManualMousePosition) {
                const sf::Vector2i mousePosition = sf::Mouse::getPosition(s_instance->window);
                mainViewFocus();
                getMainView().move({
                    static_cast<float>(s_instance->draggingViewManualMousePosition->x - mousePosition.x),
                    static_cast<float>(s_instance->draggingViewManualMousePosition->y - mousePosition.y),
                });
                s_instance->draggingViewManualMousePosition = mousePosition;
            } else {
                s_instance->draggingViewManualMousePosition = sf::Mouse::getPosition(s_instance->window);
            }
        }
    }

    void Window::resetDraggingViewManualMousePosition() {
        assert(s_instance);

        s_instance->draggingViewManualMousePosition = std::nullopt;
    }

    int Window::getZoomsCnt() {
        assert(s_instance);

        return s_instance->zoomsCnt;
    }

    void Window::increaseZoomsCnt() {
        assert(s_instance);

        s_instance->zoomsCnt++;
    }

    void Window::decreaseZoomsCnt() {
        assert(s_instance);

        s_instance->zoomsCnt--;
    }
} // namespace Screen
