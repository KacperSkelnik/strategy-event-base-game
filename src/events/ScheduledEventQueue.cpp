//
// Created by Kacper Skelnik on 05.08.2025.
//

#include "ScheduledEventQueue.h"
#include "../globals/Time.h"
#include <ranges>

ScheduledEventQueue::ScheduledEventQueue():
    events(std::map<std::shared_ptr<EventEntity>, ScheduledEvent>()) {
}

void ScheduledEventQueue::push(const std::shared_ptr<Event>& event, const sf::Time& runAt) {
    events[event->getTarget()] = ScheduledEvent{event, runAt};
}

std::vector<std::shared_ptr<Event>> ScheduledEventQueue::popReady() {
    using namespace Time;

    std::vector<std::shared_ptr<Event>> readyEvents;
    if (events.empty()) {
        return readyEvents;
    }

    for (const auto& [event, runAt] : events | std::views::values) {
        if (runAt <= Clock::now()) {
            readyEvents.push_back(event);
        }
    }

    for (const auto ready : readyEvents) {
        events.erase(ready->getTarget());
    }

    return readyEvents;
}

void ScheduledEventQueue::clear() {
    events.clear();
}