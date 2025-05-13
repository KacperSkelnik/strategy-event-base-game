//
// Created by Kacper Skelnik on 11.02.2025.
//

#include "EconomyState.h"

EconomyState::EconomyState(const int initialGold): goldAmount(initialGold) {}

void EconomyState::addGold(const int amount) {
    goldAmount += amount;
}

bool EconomyState::spendGold(const int amount) {
    if (goldAmount >= amount) {
        goldAmount -= amount;
        return true;
    }
    return false;
}

int EconomyState::getGold() const {
    return goldAmount;
}