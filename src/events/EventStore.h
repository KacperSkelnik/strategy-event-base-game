#pragma once
#include "Event.h"
#include <queue>

class EventStore final {
  private:
    std::queue<std::shared_ptr<Event>> events;

  public:
    EventStore();
    ~EventStore() = default;

    void                                                push(const std::shared_ptr<Event>& event);
    [[nodiscard]] std::optional<std::shared_ptr<Event>> front() const;
    void                                                pop();
    [[nodiscard]] unsigned long                         size() const;
};