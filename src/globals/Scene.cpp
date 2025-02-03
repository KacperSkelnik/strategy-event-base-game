//
// Created by Kacper Skelnik on 25.01.2025.
//

#include "Scene.h"

#include "Settings.h"
#include <cassert>
#include <iostream>

namespace Scene {

    static Window* s_instance = nullptr;

    bool Window::isMouseOn(const sf::Vector2i& mousePosition, const sf::View& view) {
        const auto [xStart, yStart]            = view.getViewport().position;
        const auto [windowWidth, windowHeight] = get().getSize();
        const auto [width, height]             = view.getSize();

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

        const float mainWindowHeight   = static_cast<float>(height) * 0.8f;
        const float bottomWindowHeight = static_cast<float>(height) * 0.2f;

        s_instance = new Window();

        s_instance->window = sf::RenderWindow(sf::VideoMode({width, height}), "Tower Defence");

        s_instance->mainView = sf::View(sf::FloatRect({0.f, 0.f}, {width_f, mainWindowHeight}));
        s_instance->mainView.setViewport(sf::FloatRect({0.f, 0.f}, {1, 0.8f}));

        s_instance->bottomView = sf::View(sf::FloatRect({0.f, mainWindowHeight}, {width_f, bottomWindowHeight}));
        s_instance->bottomView.setViewport(sf::FloatRect({0.f, 0.8}, {1, 0.2f}));
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

    void Window::moveMainView() {
        using namespace Settings;
        assert(s_instance);

        const sf::Vector2i mousePosition = sf::Mouse::getPosition(s_instance->window);
        const float        edgeRatio     = Variables::getViewEdgesRatio();
        const float        edgeWidth     = edgeRatio * static_cast<float>(Variables::getWindowWidth());
        const float        edgeHeight    = edgeRatio * static_cast<float>(Variables::getWindowHeight());

        if (static_cast<float>(mousePosition.x) < edgeWidth) {
            mainViewFocus();
            getMainView().move({-0.1, 0});
        }
        if (static_cast<float>(mousePosition.x) > static_cast<float>(Variables::getWindowWidth()) - edgeWidth) {
            mainViewFocus();
            getMainView().move({0.1, 0});
        }
        if (static_cast<float>(mousePosition.y) < edgeHeight) {
            mainViewFocus();
            getMainView().move({0, -0.1});
        }
        if (static_cast<float>(mousePosition.y) > static_cast<float>(Variables::getWindowHeight()) - edgeHeight) {
            mainViewFocus();
            getMainView().move({0, 0.1});
        }
    }
} // namespace Scene
