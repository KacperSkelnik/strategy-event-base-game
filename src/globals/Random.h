#pragma once

#include <random>

namespace Random {

    class RandomGenerator {
      private:
        std::mt19937 rng;

      public:
        RandomGenerator()  = default;
        ~RandomGenerator() = default;
        static void init();
        static void shutDown();

        static int   getInt(int min, int max);
        static float getFloat(float min, float max);
    };
}; // namespace Random