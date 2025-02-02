#pragma once

namespace Settings {

    class Variables {
      private:
        float    cellSize;
        unsigned windowWidth;
        unsigned windowHeight;

      public:
        Variables()  = default;
        ~Variables() = default;
        static void init();
        static void shutDown();

        static float getCellSize();
        static float getWindowWidth();
        static float getWindowHeight();

        static void setCellSize(float cellSize);
    };
} // namespace Settings
