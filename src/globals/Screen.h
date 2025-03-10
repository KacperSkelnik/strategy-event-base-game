#pragma once

#include "SFML/Graphics/RenderWindow.hpp"

namespace Screen {

    class Window {
      private:
        sf::RenderWindow            window;
        sf::View                    mainView;
        sf::View                    bottomView;
        sf::View                    rightView;
        sf::Clock                   draggingViewClock;
        std::optional<sf::Vector2i> draggingViewManualMousePosition;
        int                         zoomsCnt;

        static bool isMouseOn(const sf::Vector2i& mousePosition, const sf::View& view);

      public:
        Window()  = default;
        ~Window() = default;
        static void              init(unsigned initialWidth, unsigned initialHeight);
        static void              shutDown();
        static sf::RenderWindow& get();
        static sf::View&         getMainView();
        static void              mainViewFocus();
        static bool              isMouseOnMainView(const sf::Vector2i& mousePosition);
        static sf::View&         getBottomView();
        static void              bottomViewFocus();
        static bool              isMouseOnBottomView(const sf::Vector2i& mousePosition);
        static sf::View&         getRightView();
        static void              rightViewFocus();
        static bool              isMouseOnRightView(const sf::Vector2i& mousePosition);
        static void              dragMainView();
        static void              dragMainViewManually(bool screenCanBeDragged);
        static void              resetDraggingViewManualMousePosition();
        static int               getZoomsCnt();
        static void              increaseZoomsCnt();
        static void              decreaseZoomsCnt();
    };
} // namespace Screen