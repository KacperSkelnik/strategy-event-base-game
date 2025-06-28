//
// Created by Kacper Skelnik on 11.05.2025.
//

#include "SpendResourceHandler.h"

SpendResourceHandler::SpendResourceHandler(const SpendResourceParams params): params(params) {}

void SpendResourceHandler::invoke(const std::shared_ptr<EconomyState> target) {
    switch (params.resource) {
        case Gold:
            target->spendGold(params.amount);
            break;
    }
}