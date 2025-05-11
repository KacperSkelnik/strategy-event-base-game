//
// Created by Kacper Skelnik on 11.02.2025.
//

#include "EconomyState.h"

EconomyState::EconomyState(const long initialGold): goldAmount(initialGold) {}

void EconomyState::addGold(const long amount) {
    goldAmount += amount;
}

bool EconomyState::spendGold(const long amount) {
    if (goldAmount >= amount) {
        goldAmount -= amount;
        return true;
    }
    return false;
}

long EconomyState::getGold() const {
    return goldAmount;
}