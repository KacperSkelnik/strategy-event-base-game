//
// Created by Kacper Skelnik on 30.07.2025.
//

#include "Time.h"

#include "SFML/System/Time.hpp"

namespace Time {

    static Clock* s_clock_instance = nullptr;

    void Clock::init() {
        assert(!s_clock_instance);

        s_clock_instance = new Clock();
        s_clock_instance->clock.start();
    }

    void Clock::shutDown() {
        assert(s_clock_instance);

        s_clock_instance->clock.stop();
        delete s_clock_instance;

        s_clock_instance = nullptr;
    }

    sf::Time Clock::now() {
        assert(s_clock_instance);

        return s_clock_instance->clock.getElapsedTime();
    }
} // namespace Time
