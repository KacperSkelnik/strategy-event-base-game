//
// Created by Kacper Skelnik on 21.06.2025.
//

#include "GoForResourceHandler.h"

GoForResourceHandler::GoForResourceHandler(const std::shared_ptr<Board>& board, const GoForResourceParams& params):
    board(board),
    params(params) {
}

Event GoForResourceHandler::invoke(const std::shared_ptr<SerfCharacter> target) {
    if (params.resourcePosition == target->getPosition()) {
        target->setResource(Gold, 10);
        return {target, Idle};
    }

    board->moveCharacter(target, params.resourcePosition);
    return {target, GoForResource, params};
}
