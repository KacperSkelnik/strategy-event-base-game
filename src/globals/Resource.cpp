//
// Created by Kacper Skelnik on 25.01.2025.
//

#include "Resource.h"

namespace Resource {

    static Fonts* s_fonts_instance = nullptr;

    void Fonts::init() {
        assert(!s_fonts_instance);

        s_fonts_instance = new Fonts();

        s_fonts_instance->regular = sf::Font("/Users/kacperskelnik/CLionProjects/tower-defense/assets/Prater Sans Regular.otf");
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

} // namespace Resource