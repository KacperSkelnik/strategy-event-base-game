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

    class Textures {
      private:
        // environment
        sf::Texture grass;
        sf::Texture ground;
        sf::Texture goldRock;
        // buildings
        sf::Texture farm;
        sf::Texture goldMine;
        sf::Texture lumberjackHouse;
        sf::Texture quarry;
        sf::Texture sawMill;
        sf::Texture school;
        sf::Texture tower;
        sf::Texture townHall;
        // economy
        sf::Texture gold;
        // characters
        sf::Texture serf;

      public:
        Textures()  = default;
        ~Textures() = default;
        static void init();
        static void shutDown();
        // environment
        static sf::Texture& getGrass();
        static sf::Texture& getGround();
        static sf::Texture& getGoldRock();
        // buildings
        static sf::Texture& getFarm();
        static sf::Texture& getGoldMine();
        static sf::Texture& getLumberjackHouse();
        static sf::Texture& getQuarry();
        static sf::Texture& getSawMill();
        static sf::Texture& getSchool();
        static sf::Texture& getTower();
        static sf::Texture& getTownHall();
        // economy
        static sf::Texture& getGold();
        // characters
        static sf::Texture& getSerf();
    };
} // namespace Resource