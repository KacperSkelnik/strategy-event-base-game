#pragma once

#include "SFML/Graphics/RenderWindow.hpp"

namespace Scene {

    class Window {
      private:
        sf::RenderWindow window;
        sf::View         mainView;
        sf::View         bottomView;

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
        static void              moveMainView();
    };
} // namespace Scene