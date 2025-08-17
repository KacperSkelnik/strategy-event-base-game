//
// Created by Kacper Skelnik on 15.08.2025.
//

#include "StoreResourceHandler.h"


StoreResourceHandler::StoreResourceHandler(const std::shared_ptr<Board>&        board,
                                           const std::shared_ptr<EconomyState>& economyState,
                                           const StoreResourceParams&           params):
    board(board),
    economyState(economyState),
    params(params) {
}

Event StoreResourceHandler::invoke(const std::shared_ptr<SerfCharacter> target) {
    if (params.storagePosition == target->getPosition()) {
        const auto resource = target->getResource();
        const auto amount   = target->getAmount();
        if (resource.has_value() && amount.has_value()) {
            economyState->add(resource.value(), amount.value());
        }

        target->removeResource();

        return {target, Idle};
    }

    board->moveCharacter(target, params.storagePosition);
    return {target, StoreResource, params};
}
