#pragma once

namespace Settings {

    class Variables {
      private:
        float cellSize;

      public:
        Variables()  = default;
        ~Variables() = default;
        static void init();
        static void shutDown();

        static float getCellSize();
    };
} // namespace Settings
