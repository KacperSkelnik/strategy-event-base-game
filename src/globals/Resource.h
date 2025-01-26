//
// Created by Kacper Skelnik on 25.01.2025.
//

#ifndef RESOURCE_H
#define RESOURCE_H
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

#endif // RESOURCE_H
