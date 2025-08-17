#pragma once

#include "SFML/System/Clock.hpp"

namespace Time {

    class Clock {

    private:
        sf::Clock clock;

    public:
        Clock()  = default;
        ~Clock() = default;

        static void init();
        static void shutDown();

        static sf::Time now();
    };
} // namespace Time