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
        s_variables_instance->cellSize           = 32;
        s_variables_instance->windowWidth        = 800;
        s_variables_instance->windowHeight       = 1000;
        s_variables_instance->viewDraggingPart   = 0.05;
        s_variables_instance->viewDraggingOffset = 0.1;
        s_variables_instance->viewDraggingTime   = sf::seconds(0.25);
    }

    void Variables::shutDown() {
        assert(s_variables_instance);

        delete s_variables_instance;

        s_variables_instance = nullptr;
    }

    float Variables::getCellSize() {
        assert(s_variables_instance);

        return s_variables_instance->cellSize;
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

    void Variables::setCellSize(const float cellSize) {
        assert(s_variables_instance);

        s_variables_instance->cellSize = cellSize;
    }
} // namespace Settings