#pragma once
#include "Event.h"
#include "EventStore.h"

class EventQueue final {
  private:
    EventStore eventQueue;

  public:
    EventQueue()  = default;
    ~EventQueue() = default;

    void enqueue(const std::shared_ptr<Event>& event);
};