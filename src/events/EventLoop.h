#pragma once
#include "../board/Board.h"
#include "../economy/EconomyState.h"
#include "EventQueue.h"
#include "ScheduledEventQueue.h"

class EventLoop {

private:
    std::shared_ptr<EventQueue>          eventQueue;
    std::shared_ptr<ScheduledEventQueue> scheduledEventQueue;
    std::shared_ptr<EconomyState>        economyState;
    std::shared_ptr<Board>               board;

    void applyEvent(const std::shared_ptr<Event>& event) const;

public:
    explicit EventLoop(
        const std::shared_ptr<EventQueue>&          eventQueue,
        const std::shared_ptr<ScheduledEventQueue>& scheduledEventQueue,
        const std::shared_ptr<EconomyState>&        economyState,
        const std::shared_ptr<Board>&               board
    );
    ~EventLoop() = default;

    void drain() const;
    void stop() const;
};