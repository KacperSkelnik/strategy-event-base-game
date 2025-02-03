#pragma once
#include "SFML/System/Time.hpp"

namespace Settings {

    class Variables {
      private:
        float    cellSize;
        unsigned windowWidth;
        unsigned windowHeight;
        float    viewDraggingPart;
        float    viewDraggingOffset;
        sf::Time viewDraggingTime;

      public:
        Variables()  = default;
        ~Variables() = default;
        static void init();
        static void shutDown();

        static float    getCellSize();
        static unsigned getWindowWidth();
        static unsigned getWindowHeight();
        static float    getViewDraggingPart();
        static float    getViewDraggingOffset();
        static sf::Time getViewDraggingTime();

        static void setCellSize(float cellSize);
    };
} // namespace Settings
