//
// Created by Kacper Skelnik on 23.07.2025.
//

#include "IdleHandler.h"

#include "../SerfCharacter.h"
#include "../../../globals/Time.h"
#include "../../buildings/ResourceFactory.h"
#include <iostream>

IdleHandler::IdleHandler(const std::shared_ptr<Board>& board): board(board) {
}

struct BuildingWithDistance {
    std::shared_ptr<Building> building = nullptr;
    unsigned int              distance = 65535; // max value
};

Event IdleHandler::storeResource(const std::shared_ptr<SerfCharacter>& serf) const {
    BuildingWithDistance chosenBuilding;
    for (const auto& building : board->getBuildings()) {
        if (building->getType() == TownHall) {
            const unsigned int distance =
                board->getDistance(serf->getPosition(), building->getPosition());
            if (chosenBuilding.building == nullptr || distance < chosenBuilding.distance) {
                chosenBuilding.building = building;
                chosenBuilding.distance = distance;
            }
        }
    }

    if (chosenBuilding.building == nullptr) { return {serf, Idle}; }

    const auto params = StoreResourceParams{chosenBuilding.building->getPosition()};
    return {serf, StoreResource, params};
}

struct FactoryWithDistance {
    std::shared_ptr<ResourceFactory> factory  = nullptr;
    unsigned int                     distance = 65535; // max value
};

Event IdleHandler::goForResource(const std::shared_ptr<SerfCharacter>& serf) const {
    FactoryWithDistance chosenFactory;
    for (const auto& building : board->getBuildings()) {
        if (building->isFactory()) {
            const std::shared_ptr<ResourceFactory> factory = std::static_pointer_cast<ResourceFactory>(building);
            if (!factory->isSerfComing()) {
                const unsigned int distance =
                    board->getDistance(serf->getPosition(), factory->getPosition());
                if (chosenFactory.factory == nullptr || distance < chosenFactory.distance) {
                    chosenFactory.factory  = factory;
                    chosenFactory.distance = distance;
                }
            }
        }
    }

    if (chosenFactory.factory == nullptr) { return {serf, Idle}; }

    chosenFactory.factory->setSerfIsComing(true);
    const auto params = GoForResourceParams{chosenFactory.factory};
    return {serf, GoForResource, params};
}

Event IdleHandler::determineNextEvent(const std::shared_ptr<Character>& target) const {
    using namespace Time;

    switch (target->getType()) {
        case Serf: {
            const std::shared_ptr<SerfCharacter> serf = std::static_pointer_cast<SerfCharacter>(target);
            if (serf->carriesResource()) { return storeResource(serf); }
            return goForResource(serf);
        }
        default: {
            throw std::runtime_error("Unsupported character type for IdleHandler!");
        }
    }
}

bool IdleHandler::isCharacterInsideOfBuilding(const std::shared_ptr<Character>& target) const {
    return std::ranges::any_of(board->getBuildings(),
                               [&](const std::shared_ptr<Building>& building) {
                                   return building->getPosition() == target->getPosition();
                               });
}

Event IdleHandler::invoke(const std::shared_ptr<Character> target) {
    Event nextEvent = determineNextEvent(target);

    if (nextEvent.getEventType() == Idle && isCharacterInsideOfBuilding(target)) {
        const GridPosition destination = board->getClosestFreeSpace(target->getPosition());
        return {target, GoTo, GoToParams{destination}};
    }

    target->setCurrentAction(nextEvent.getEventType());
    return nextEvent;
}