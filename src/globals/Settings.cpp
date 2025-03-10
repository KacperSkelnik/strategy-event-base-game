//
// Created by Kacper Skelnik on 02.02.2025.
//

#include "Settings.h"

#include <cassert>

namespace Settings {

    static Variables* s_variables_instance = nullptr;

    void Variables::init() {
        assert(!s_variables_instance);

        s_variables_instance                     = new Variables();
        s_variables_instance->spriteWidth        = 95;
        s_variables_instance->spriteHeight       = 97;
        s_variables_instance->windowWidth        = 1600;
        s_variables_instance->windowHeight       = 1200;
        s_variables_instance->viewDraggingPart   = 0.05;
        s_variables_instance->viewDraggingOffset = 2;
        s_variables_instance->viewDraggingTime   = sf::seconds(0.2);
        s_variables_instance->zoomFactor         = 0.05;
        s_variables_instance->maxZoomsCnt        = 5;
        s_variables_instance->minZoomsCnt        = -20;
    }

    void Variables::shutDown() {
        assert(s_variables_instance);

        delete s_variables_instance;

        s_variables_instance = nullptr;
    }

    float Variables::getSpriteWidth() {
        assert(s_variables_instance);

        return s_variables_instance->spriteWidth;
    }

    float Variables::getSpriteHeight() {
        assert(s_variables_instance);

        return s_variables_instance->spriteHeight;
    }

    unsigned Variables::getWindowWidth() {
        assert(s_variables_instance);

        return s_variables_instance->windowWidth;
    }

    unsigned Variables::getWindowHeight() {
        assert(s_variables_instance);

        return s_variables_instance->windowHeight;
    }

    float Variables::getViewDraggingPart() {
        assert(s_variables_instance);

        return s_variables_instance->viewDraggingPart;
    }

    float Variables::getViewDraggingOffset() {
        assert(s_variables_instance);

        return s_variables_instance->viewDraggingOffset;
    }

    sf::Time Variables::getViewDraggingTime() {
        assert(s_variables_instance);

        return s_variables_instance->viewDraggingTime;
    }

    float Variables::getZoomFactor() {
        assert(s_variables_instance);

        return s_variables_instance->zoomFactor;
    }

    int Variables::getMaxZoomsCnt() {
        assert(s_variables_instance);

        return s_variables_instance->maxZoomsCnt;
    }

    int Variables::getMinZoomsCnt() {
        assert(s_variables_instance);

        return s_variables_instance->minZoomsCnt;
    }
} // namespace Settings