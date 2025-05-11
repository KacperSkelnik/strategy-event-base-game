#pragma once
#include "Event.h"
#include "EventStore.h"

class EventQueue final {
  private:
    EventStore eventStore;

  public:
    EventQueue();
    ~EventQueue() = default;

    void                                                push(const std::shared_ptr<Event>& event);
    [[nodiscard]] std::optional<std::shared_ptr<Event>> front() const;
    void                                                pop();
    [[nodiscard]] unsigned long                         size() const;
};