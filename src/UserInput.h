#pragma once
#include "board/Board.h"
#include "board/buildings/BuildingType.h"
#include "events/EventQueue.h"
#include "interface/BuildingSelector.h"
#include "SFML/Window/Event.hpp"

class UserInput final {

private:
    std::shared_ptr<Board>            board;
    std::shared_ptr<EventQueue>       eventQueue;
    std::shared_ptr<BuildingSelector> buildingSelector;
    bool                              screenCanBeDragged;

    std::optional<BuildingType> selectedBuilding;
    bool                        roadSelected;
    static void                 onClose();
    void                        onMousePress(const sf::Event::MouseButtonPressed* event);
    void                        onMouseRelease(const sf::Event::MouseButtonReleased* event);
    void                        onMouseScroll(const sf::Event::MouseWheelScrolled* event) const;

public:
    UserInput() = delete;
    explicit UserInput(const std::shared_ptr<Board>&            board,
                       const std::shared_ptr<EventQueue>&       eventQueue,
                       const std::shared_ptr<BuildingSelector>& buildingSelector);
    ~UserInput() = default;

    void                        handleEvent();
    std::optional<BuildingType> getSelectedBuilding() const { return selectedBuilding; }
    bool                        isRoadSelected() const { return roadSelected; }
};