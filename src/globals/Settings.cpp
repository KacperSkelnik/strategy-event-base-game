//
// Created by Kacper Skelnik on 02.02.2025.
//

#include "Settings.h"

#include <cassert>
#include <fstream>

namespace Settings {

    static Variables* s_variables_instance = nullptr;

    void Variables::init() {
        assert(!s_variables_instance);

        std::ifstream file("config/game.json");
        if (!file.is_open()) {
            throw std::runtime_error("Failed to open ../config/game.json");
        }

        nlohmann::json jsonConfig;
        try {
            file >> jsonConfig;
        } catch (const nlohmann::json::parse_error& e) {
            throw std::runtime_error("Failed to parse JSON: " + std::string(e.what()));
        }

        s_variables_instance         = new Variables();
        s_variables_instance->config = jsonConfig.get<Config>();
    }

    void Variables::shutDown() {
        assert(s_variables_instance);

        delete s_variables_instance;

        s_variables_instance = nullptr;
    }

    float Variables::getSpriteWidth() {
        assert(s_variables_instance);

        return s_variables_instance->config.graphics.spriteWidth;
    }

    float Variables::getSpriteHeight() {
        assert(s_variables_instance);

        return s_variables_instance->config.graphics.spriteHeight;
    }

    unsigned Variables::getWindowWidth() {
        assert(s_variables_instance);

        return s_variables_instance->config.window.windowWidth;
    }

    unsigned Variables::getWindowHeight() {
        assert(s_variables_instance);

        return s_variables_instance->config.window.windowHeight;
    }

    float Variables::getViewDraggingPart() {
        assert(s_variables_instance);

        return s_variables_instance->config.view.viewDraggingPart;
    }

    float Variables::getViewDraggingOffset() {
        assert(s_variables_instance);

        return s_variables_instance->config.view.viewDraggingOffset;
    }

    sf::Time Variables::getViewDraggingTime() {
        assert(s_variables_instance);

        return s_variables_instance->config.view.viewDraggingTime;
    }

    float Variables::getZoomFactor() {
        assert(s_variables_instance);

        return s_variables_instance->config.view.zoomFactor;
    }

    int Variables::getMaxZoomsCnt() {
        assert(s_variables_instance);

        return s_variables_instance->config.view.maxZoomsCnt;
    }

    int Variables::getMinZoomsCnt() {
        assert(s_variables_instance);

        return s_variables_instance->config.view.minZoomsCnt;
    }

    sf::Time Variables::getClockTickDuration() {
        assert(s_variables_instance);

        return s_variables_instance->config.game.clockTickDuration;
    }
} // namespace Settings