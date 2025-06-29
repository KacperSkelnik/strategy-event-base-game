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

        s_fonts_instance->regular = sf::Font("../assets/Prater Sans Regular.otf");
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
        s_textures_instance->grass    = sf::Texture("../assets/textures/environment/grass.png");
        s_textures_instance->ground   = sf::Texture("../assets/textures/environment/ground.png");
        s_textures_instance->goldRock = sf::Texture("../assets/textures/environment/gold.png");
        // buildings
        s_textures_instance->farm            = sf::Texture("../assets/textures/buildings/farm.png");
        s_textures_instance->goldMine        = sf::Texture("../assets/textures/buildings/gold_mine.png");
        s_textures_instance->lumberjackHouse = sf::Texture("../assets/textures/buildings/lumberjack_house.png");
        s_textures_instance->quarry          = sf::Texture("../assets/textures/buildings/quarry.png");
        s_textures_instance->sawMill         = sf::Texture("../assets/textures/buildings/saw_mill.png");
        s_textures_instance->school          = sf::Texture("../assets/textures/buildings/school.png");
        s_textures_instance->tower           = sf::Texture("../assets/textures/buildings/tower.png");
        s_textures_instance->townHall        = sf::Texture("../assets/textures/buildings/town_hall.png");
        // economy
        s_textures_instance->gold = sf::Texture("../assets/textures/economy/gold.png");
        // characters
        s_textures_instance->serf = sf::Texture("../assets/textures/characters/serf.png");
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

} // namespace Resource