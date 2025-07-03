//
// Created by Kacper Skelnik on 11.02.2025.
//

#include "EconomyState.h"

EconomyState::EconomyState(const int initialGold) {
    resources[Gold] = initialGold;
}

void EconomyState::add(const EconomyResource type, const int amount) {
    resources[type] += amount;
}

bool EconomyState::trySpend(const EconomyResource type, const int amount) {
    if (canAfford(type, amount)) {
        resources[type] -= amount;
        return true;
    }
    return false;
}

int EconomyState::getResourceAmount(const EconomyResource type) const {
    const auto it = resources.find(type);
    if (it != resources.end()) {
        return it->second;
    }
    return 0;
}

bool EconomyState::canAfford(const EconomyResource type, const int amount) const {
    auto it = resources.find(type);
    if (it != resources.end()) {
        return it->second >= amount;
    }
    return false;
}
