#pragma once
#include "Character.h"

class SerfCharacter final: public Character {

public:
    explicit SerfCharacter(CharacterType type, GridPosition position);
    ~SerfCharacter() override = default;
};