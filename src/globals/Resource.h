#pragma once

#include "SFML/Graphics/Font.hpp"

namespace Resource {

    class Fonts {
      private:
        sf::Font regular;

      public:
        Fonts()  = default;
        ~Fonts() = default;
        static void      init();
        static void      shutDown();
        static sf::Font& getRegular();
    };
} // namespace Resource