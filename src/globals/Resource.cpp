//
// Created by Kacper Skelnik on 25.01.2025.
//

#include "Resource.h"

#include "Settings.h"
#include <iostream>

namespace Resource {

    // Fonts
    static Fonts* s_fonts_instance = nullptr;

    void Fonts::init() {
        assert(!s_fonts_instance);

        s_fonts_instance = new Fonts();

        if (!s_fonts_instance->regular.openFromFile("assets/Prater Sans Regular.otf")) {
            throw std::runtime_error("Failed to load Prater Sans Regular.otf");
        }
    }

    void Fonts::shutDown() {
        assert(s_fonts_instance);

        delete s_fonts_instance;

        s_fonts_instance = nullptr;
    }

    sf::Font& Fonts::getRegular() {
        assert(s_fonts_instance);

        return s_fonts_instance->regular;
    }

    // Textures
    static Textures* s_textures_instance = nullptr;

    void Textures::init() {
        assert(!s_textures_instance);
        using namespace Settings;

        s_textures_instance = new Textures();

        // environment
        if (!s_textures_instance->grass.loadFromFile("assets/textures/environment/grass.png")) {
            throw std::runtime_error("Failed to load grass.png");
        }
        if (!s_textures_instance->ground.loadFromFile("assets/textures/environment/ground.png")) {
            throw std::runtime_error("Failed to load ground.png");
        }
        if (!s_textures_instance->goldRock.loadFromFile("assets/textures/environment/gold.png")) {
            throw std::runtime_error("Failed to load gold.png");
        }
        // buildings
        if (!s_textures_instance->farm.loadFromFile("assets/textures/buildings/farm.png")) {
            throw std::runtime_error("Failed to load farm.png");
        }
        if (!s_textures_instance->goldMine.loadFromFile("assets/textures/buildings/gold_mine.png")) {
            throw std::runtime_error("Failed to load gold_mine.png");
        }
        if (!s_textures_instance->lumberjackHouse.loadFromFile("assets/textures/buildings/lumberjack_house.png")) {
            throw std::runtime_error("Failed to load lumberjack_house.png");
        }
        if (!s_textures_instance->quarry.loadFromFile("assets/textures/buildings/quarry.png")) {
            throw std::runtime_error("Failed to load quarry.png");
        }
        if (!s_textures_instance->sawMill.loadFromFile("assets/textures/buildings/saw_mill.png")) {
            throw std::runtime_error("Failed to load saw_mill.png");
        }
        if (!s_textures_instance->school.loadFromFile("assets/textures/buildings/school.png")) {
            throw std::runtime_error("Failed to load school.png");
        }
        if (!s_textures_instance->tower.loadFromFile("assets/textures/buildings/tower.png")) {
            throw std::runtime_error("Failed to load tower.png");
        }
        if (!s_textures_instance->townHall.loadFromFile("assets/textures/buildings/town_hall.png")) {
            throw std::runtime_error("Failed to load town_hall.png");
        }
        // economy
        if (!s_textures_instance->gold.loadFromFile("assets/textures/economy/gold.png")) {
            throw std::runtime_error("Failed to load gold.png");
        }
        // characters
        if (!s_textures_instance->serf.loadFromFile("assets/textures/characters/serf.png")) {
            throw std::runtime_error("Failed to load serf.png");
        }
        // roads
        if (!s_textures_instance->road.loadFromFile("assets/textures/roads/road.png")) {
            throw std::runtime_error("Failed to load road.png");
        }
    }

    void Textures::shutDown() {
        assert(s_textures_instance);

        delete s_textures_instance;

        s_textures_instance = nullptr;
    }

    sf::Texture& Textures::getGrass() {
        assert(s_textures_instance);

        return s_textures_instance->grass;
    }

    sf::Texture& Textures::getGround() {
        assert(s_textures_instance);

        return s_textures_instance->ground;
    }

    sf::Texture& Textures::getGoldRock() {
        assert(s_textures_instance);

        return s_textures_instance->goldRock;
    }

    sf::Texture& Textures::getFarm() {
        assert(s_textures_instance);

        return s_textures_instance->farm;
    }

    sf::Texture& Textures::getGoldMine() {
        assert(s_textures_instance);

        return s_textures_instance->goldMine;
    }

    sf::Texture& Textures::getLumberjackHouse() {
        assert(s_textures_instance);

        return s_textures_instance->lumberjackHouse;
    }

    sf::Texture& Textures::getQuarry() {
        assert(s_textures_instance);

        return s_textures_instance->quarry;
    }

    sf::Texture& Textures::getSawMill() {
        assert(s_textures_instance);

        return s_textures_instance->sawMill;
    }

    sf::Texture& Textures::getSchool() {
        assert(s_textures_instance);

        return s_textures_instance->school;
    }

    sf::Texture& Textures::getTower() {
        assert(s_textures_instance);

        return s_textures_instance->tower;
    }

    sf::Texture& Textures::getTownHall() {
        assert(s_textures_instance);

        return s_textures_instance->townHall;
    }

    sf::Texture& Textures::getGold() {
        assert(s_textures_instance);

        return s_textures_instance->gold;
    }

    sf::Texture& Textures::getSerf() {
        assert(s_textures_instance);

        return s_textures_instance->serf;
    }

    sf::Texture& Textures::getRoad() {
        assert(s_textures_instance);

        return s_textures_instance->road;
    }

} // namespace Resource