//
// Created by Kacper Skelnik on 21.06.2025.
//

#include "Random.h"

#include <cassert>

namespace Random {

    static RandomGenerator* s_random_generator_instance = nullptr;

    void RandomGenerator::init() {
        assert(!s_random_generator_instance);

        s_random_generator_instance = new RandomGenerator();
    }

    void RandomGenerator::shutDown() {
        assert(s_random_generator_instance);

        delete s_random_generator_instance;

        s_random_generator_instance = nullptr;
    }

    int RandomGenerator::getInt(const int min, const int max) {
        assert(s_random_generator_instance);
        assert(min < max);

        std::uniform_int_distribution dist(min, max);
        return dist(s_random_generator_instance->rng);
    }

    float RandomGenerator::getFloat(const float min, const float max) {
        assert(s_random_generator_instance);
        assert(min < max);

        std::uniform_real_distribution dist(min, max);
        return dist(s_random_generator_instance->rng);
    }
} // namespace Random