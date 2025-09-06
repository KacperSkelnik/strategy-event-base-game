//
// Created by Kacper Skelnik on 21.06.2025.
//

#include "GoForResourceHandler.h"

#include <utility>

GoForResourceHandler::GoForResourceHandler(const std::shared_ptr<Board>& board, GoForResourceParams params):
    board(board),
    params(std::move(params)) {
}

Event GoForResourceHandler::invoke(const std::shared_ptr<SerfCharacter> target) {
    if (params.factory->getPosition() == target->getPosition()) {
        target->setResource(params.factory->getProducedResource(), params.factory->getProductionAmount());
        params.factory->setSerfIsComing(false);
        return {target, Idle};
    }

    board->moveCharacter(target, params.factory->getPosition());
    return {target, GoForResource, std::move(params)};
}
