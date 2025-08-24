#pragma once
#include "Event.h"
#include <map>

typedef std::map<std::shared_ptr<EventEntity>, std::shared_ptr<Event>> Storage;

class EventQueue final {

private:
    Storage events;

public:
    EventQueue();
    ~EventQueue() = default;

    void                                                push(const std::shared_ptr<Event>& event);
    [[nodiscard]] std::optional<std::shared_ptr<Event>> pop();
    bool                                                empty() const;
    void                                                clear();
};