//
// Created by Kacper Skelnik on 21.06.2025.
//

#include "Character.h"

Character::Character(const CharacterType type, const GridPosition position):
    type(type),
    position(position),
    currentAction(Idle) {}