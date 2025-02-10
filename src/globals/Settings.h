#pragma once
#include "SFML/System/Time.hpp"

namespace Settings {

    class Variables {
      private:
        float    spriteWidth;
        float    spriteHeight;
        unsigned windowWidth;
        unsigned windowHeight;
        float    viewDraggingPart;
        float    viewDraggingOffset;
        sf::Time viewDraggingTime;
        float    zoomFactor;
        int      maxZoomsCnt;
        int      minZoomsCnt;

      public:
        Variables()  = default;
        ~Variables() = default;
        static void init();
        static void shutDown();

        static float    getSpriteWidth();
        static float    getSpriteHeight();
        static unsigned getWindowWidth();
        static unsigned getWindowHeight();
        static float    getViewDraggingPart();
        static float    getViewDraggingOffset();
        static sf::Time getViewDraggingTime();
        static float    getZoomFactor();
        static int      getMaxZoomsCnt();
        static int      getMinZoomsCnt();
    };
} // namespace Settings
