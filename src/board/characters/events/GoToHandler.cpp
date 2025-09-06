//
// Created by Kacper Skelnik on 06.09.2025.
//

#include "GoToHandler.h"

GoToHandler::GoToHandler(const std::shared_ptr<Board>& board, const GoToParams params):
    board(board),
    params(std::move(params)) {
}

Event GoToHandler::invoke(std::shared_ptr<Character> target) {
    if (params.destination == target->getPosition()) {
        return {target, Idle};
    }

    board->moveCharacter(target, params.destination);
    return Event{target, GoTo, std::move(params)};
}