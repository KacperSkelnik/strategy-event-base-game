//
// Created by Kacper Skelnik on 25.01.2025.
//

#ifndef GLOBALS_H
#define GLOBALS_H
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
    };
} // namespace Scene

#endif // GLOBALS_H
