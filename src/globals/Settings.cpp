//
// Created by Kacper Skelnik on 02.02.2025.
//

#include "Settings.h"

#include <cassert>

namespace Settings {

    static Variables* s_variables_instance = nullptr;

    void Variables::init() {
        assert(!s_variables_instance);

        s_variables_instance                 = new Variables();
        s_variables_instance->cellSize       = 32;
        s_variables_instance->windowWidth    = 800;
        s_variables_instance->windowHeight   = 1000;
        s_variables_instance->viewEdgesRatio = 0.05;
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

    float Variables::getViewEdgesRatio() {
        assert(s_variables_instance);

        return s_variables_instance->viewEdgesRatio;
    }

    void Variables::setCellSize(const float cellSize) {
        assert(s_variables_instance);

        s_variables_instance->cellSize = cellSize;
    }
} // namespace Settings