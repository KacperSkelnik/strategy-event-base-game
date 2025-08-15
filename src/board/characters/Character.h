#pragma once

#include "../../events/EventEntity.h"
#include "../../events/EventType.h"
#include "../GridPosition.h"
#include "CharacterType.h"

class Character: public EventEntity {

protected:
    CharacterType type;
    GridPosition  position;
    EventType     currentAction;

public:
    Character() = delete;
    explicit Character(CharacterType type, GridPosition position);
    ~Character() override = default;

    [[nodiscard]] CharacterType getType() const { return type; }
    [[nodiscard]] GridPosition  getPosition() const { return position; }
    void                        setPosition(const GridPosition newPosition) { position = newPosition; }
    void                        setCurrentAction(const EventType action) { currentAction = action; }
    void                        makeIdle() { currentAction = Idle; }
};