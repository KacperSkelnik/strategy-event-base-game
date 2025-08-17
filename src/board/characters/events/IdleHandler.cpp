//
// Created by Kacper Skelnik on 23.07.2025.
//

#include "IdleHandler.h"

#include "../SerfCharacter.h"
#include "../../../globals/Time.h"

IdleHandler::IdleHandler(const std::shared_ptr<Board>& board): board(board) {
}

Event IdleHandler::determineNextEvent(const std::shared_ptr<Character>& target) const {
    using namespace Time;

    switch (target->getType()) {
        case Serf: {
            std::shared_ptr<SerfCharacter> serf = std::static_pointer_cast<SerfCharacter>(target);
            if (serf->carriesResource()) {
                for (const auto& building : board->getBuildings()) {
                    if (building->getType() == TownHall) {
                        const auto params = StoreResourceParams{building->getPosition()};
                        return {serf, StoreResource, params};
                    }
                }
            } else {
                for (const auto& building : board->getBuildings()) {
                    if (building->isFactory()) {
                        const auto params = GoForResourceParams{building->getPosition()};
                        return {serf, GoForResource, params};
                    }
                }
            }
            return {target, Idle};
        }
        default: {
            throw std::runtime_error("Unsupported character type for IdleHandler!");
        }
    }
}

Event IdleHandler::invoke(const std::shared_ptr<Character> target) {
    Event nextEvent = determineNextEvent(target);
    target->setCurrentAction(nextEvent.getEventType());
    return nextEvent;
}