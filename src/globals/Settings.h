#pragma once
#include "SFML/System/Time.hpp"
#include <nlohmann/json.hpp>

template <> struct nlohmann::adl_serializer<sf::Time> {
    static void to_json(json& j, const sf::Time& time) { j = time.asSeconds(); }

    static void from_json(const json& j, sf::Time& time) { time = sf::seconds(j.get<float>()); }
};

namespace Settings {

    struct GraphicsConfig {
        float spriteWidth;
        float spriteHeight;
    };

    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(GraphicsConfig, spriteWidth, spriteHeight);

    struct WindowConfig {
        unsigned windowWidth;
        unsigned windowHeight;
    };

    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(WindowConfig, windowWidth, windowHeight);

    struct ViewConfig {
        float    viewDraggingPart;
        float    viewDraggingOffset;
        sf::Time viewDraggingTime;
        float    zoomFactor;
        int      maxZoomsCnt;
        int      minZoomsCnt;
    };

    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(ViewConfig,
                                       viewDraggingPart,
                                       viewDraggingOffset,
                                       viewDraggingTime,
                                       zoomFactor,
                                       maxZoomsCnt,
                                       minZoomsCnt);

    struct GameConfig {
        sf::Time clockTickDuration;
    };

    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(GameConfig, clockTickDuration);

    struct Config {
        GraphicsConfig graphics;
        WindowConfig   window;
        ViewConfig     view;
        GameConfig     game;
    };

    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Config, graphics, window, view, game);

    class Variables {

    private:
        Config config;

    public:
        Variables()  = default;
        ~Variables() = default;
        static void init();
        static void shutDown();

        static float getSpriteWidth();
        static float getSpriteHeight();

        static unsigned getWindowWidth();
        static unsigned getWindowHeight();

        static float    getViewDraggingPart();
        static float    getViewDraggingOffset();
        static sf::Time getViewDraggingTime();
        static float    getZoomFactor();
        static int      getMaxZoomsCnt();
        static int      getMinZoomsCnt();

        static sf::Time getClockTickDuration();
    };
} // namespace Settings
