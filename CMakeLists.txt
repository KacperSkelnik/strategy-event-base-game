cmake_minimum_required(VERSION 3.28)
project(tower-defence)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 3.0.1
        GIT_SHALLOW ON
        EXCLUDE_FROM_ALL
        SYSTEM)
FetchContent_MakeAvailable(SFML)

FetchContent_Declare(nlohmann
        GIT_REPOSITORY https://github.com/nlohmann/json.git
        GIT_TAG v3.12.0)
FetchContent_MakeAvailable(nlohmann)

add_executable(main src/main.cpp
        src/board/Grid.cpp
        src/board/Grid.h
        src/globals/Screen.cpp
        src/globals/Screen.h
        src/globals/Resource.cpp
        src/globals/Resource.h
        src/Game.cpp
        src/Game.h
        src/interface/BuildingSelector.cpp
        src/interface/BuildingSelector.h
        src/board/buildings/Building.cpp
        src/board/buildings/Building.h
        src/globals/Settings.cpp
        src/globals/Settings.h
        src/board/GridPosition.h
        src/board/buildings/BuildingType.h
        src/interface/EconomyPanel.cpp
        src/interface/EconomyPanel.h
        src/economy/EconomyState.cpp
        src/economy/EconomyState.h
        src/interface/EconomyCell.cpp
        src/interface/EconomyCell.h
        src/events/Event.h
        src/events/EventQueue.cpp
        src/events/EventQueue.h
        src/events/EventEntity.h
        src/events/EventHandler.h
        src/events/Event.cpp
        src/board/Board.cpp
        src/board/Board.h
        src/board/buildings/events/CreateBuildingHandler.cpp
        src/board/buildings/events/CreateBuildingHandler.h
        src/events/EventLoop.cpp
        src/events/EventLoop.h
        src/economy/events/SpendResourceHandler.cpp
        src/economy/events/SpendResourceHandler.h
        src/economy/EconomyResource.h
        src/globals/Random.cpp
        src/globals/Random.h
        src/board/characters/events/CreateCharacterHandler.h
        src/board/characters/Character.cpp
        src/board/characters/Character.h
        src/board/characters/CharacterType.h
        src/events/EventParams.h
        src/board/characters/events/GoForResourceHandler.h
        src/board/characters/events/GoForResourceHandler.cpp
        src/board/OccupationType.h
        src/board/buildings/ResourceFactory.cpp
        src/board/buildings/ResourceFactory.h
        src/board/characters/SerfCharacter.cpp
        src/board/characters/SerfCharacter.h
        src/board/characters/events/IdleHandler.cpp
        src/board/characters/events/IdleHandler.h
        src/globals/Time.cpp
        src/globals/Time.h
        src/events/ScheduledEventQueue.cpp
        src/events/ScheduledEventQueue.h
        src/board/characters/events/CreateCharacterHandler.cpp
)

target_compile_features(main PRIVATE cxx_std_17)
target_link_libraries(main PRIVATE SFML::Graphics)
target_link_libraries(main PRIVATE nlohmann_json)