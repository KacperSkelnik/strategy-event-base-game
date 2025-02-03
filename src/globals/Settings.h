#pragma once

namespace Settings {

    class Variables {
      private:
        float    cellSize;
        unsigned windowWidth;
        unsigned windowHeight;
        float    viewEdgesRatio;

      public:
        Variables()  = default;
        ~Variables() = default;
        static void init();
        static void shutDown();

        static float    getCellSize();
        static unsigned getWindowWidth();
        static unsigned getWindowHeight();
        static float    getViewEdgesRatio();

        static void setCellSize(float cellSize);
    };
} // namespace Settings
