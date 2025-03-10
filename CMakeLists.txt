cmake_minimum_required(VERSION 3.28)
project(tower-defence)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 3.0.0
        GIT_SHALLOW ON
        EXCLUDE_FROM_ALL
        SYSTEM)
FetchContent_MakeAvailable(SFML)

FetchContent_Declare(nlohmann
        GIT_REPOSITORY https://github.com/nlohmann/json.git
        GIT_TAG v3.10.5)
FetchContent_MakeAvailable(nlohmann)

add_executable(main src/main.cpp
        src/interface/grid.cpp
        src/interface/grid.h
        src/globals/Screen.cpp
        src/globals/Screen.h
        src/globals/Resource.cpp
        src/globals/Resource.h
        src/Game.cpp
        src/Game.h
        src/interface/BuildingSelector.cpp
        src/interface/BuildingSelector.h
        src/board/Building.cpp
        src/board/Building.h
        src/globals/Settings.cpp
        src/globals/Settings.h
        src/interface/GridPosition.h
        src/board/BuildingType.h
        src/interface/EconomyPanel.cpp
        src/interface/EconomyPanel.h
        src/EconomyState.cpp
        src/EconomyState.h
        src/interface/EconomyCell.cpp
        src/interface/EconomyCell.h
)

target_compile_features(main PRIVATE cxx_std_17)
target_link_libraries(main PRIVATE SFML::Graphics)
target_link_libraries(main PRIVATE nlohmann_json)