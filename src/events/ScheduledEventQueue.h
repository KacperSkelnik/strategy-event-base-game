#pragma once
#include "Event.h"
#include "SFML/System/Time.hpp"
#include <map>

struct ScheduledEvent {
    std::shared_ptr<Event> event;
    sf::Time               runAt;
};

typedef std::map<std::shared_ptr<EventEntity>, ScheduledEvent> ScheduledStorage;

class ScheduledEventQueue final {

private:
    ScheduledStorage events;

public:
    ScheduledEventQueue();
    ~ScheduledEventQueue() = default;

    void                                              push(const std::shared_ptr<Event>& event, const sf::Time& runAt);
    [[nodiscard]] std::vector<std::shared_ptr<Event>> popReady();
    void                                              clear();
};