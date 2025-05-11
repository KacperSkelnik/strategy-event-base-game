//
// Created by Kacper Skelnik on 11.05.2025.
//

#include "SpendResourceHandler.h"

SpendResourceHandler::SpendResourceHandler(const EconomyResource resource, const long amount):
    resource(resource),
    amount(amount) {}

void SpendResourceHandler::invoke(const std::shared_ptr<EconomyState> target) {
    switch (resource) {
        case Gold:
            target->spendGold(amount);
            break;
    }
}