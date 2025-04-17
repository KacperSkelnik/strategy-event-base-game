#pragma once
#include "EventQueue.h"

class EventLoop {
  private:
    std::shared_ptr<EventQueue> eventQueue;

  public:
    explicit EventLoop(const std::shared_ptr<EventQueue>& eventQueue);
    ~EventLoop() = default;

    void runSingle() const;
};