#pragma once

#include "../../events/EventEntity.h"
#include "../GridPosition.h"
#include "CharacterType.h"

class Character final: public EventEntity {
  private:
    CharacterType type;
    GridPosition  position;

  public:
    Character() = delete;
    explicit Character(CharacterType type, GridPosition position);
    ~Character() override = default;

    CharacterType getType() const { return type; }
    GridPosition  getPosition() const { return position; }
};