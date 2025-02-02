//
// Created by Kacper Skelnik on 02.02.2025.
//

#include "Settings.h"

#include <cassert>

namespace Settings {

    static Variables* s_variables_instance = nullptr;

    void Variables::init() {
        assert(!s_variables_instance);

        s_variables_instance           = new Variables();
        s_variables_instance->cellSize = 32;
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
} // namespace Settings