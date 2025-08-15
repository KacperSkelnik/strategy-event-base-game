#pragma once

/**
 * Every Object in the game that wants to be targeted by events has to implement this class.
 */
class EventEntity {

public:
    virtual ~EventEntity() = default;
};