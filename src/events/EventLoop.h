#pragma once
#include "../economy/EconomyState.h"
#include "EventQueue.h"

class EventLoop {
  private:
    std::shared_ptr<EventQueue>   eventQueue;
    std::shared_ptr<EconomyState> economyState;

  public:
    explicit EventLoop(const std::shared_ptr<EventQueue>& eventQueue, const std::shared_ptr<EconomyState>& economyState);
    ~EventLoop() = default;

    void run() const;
};