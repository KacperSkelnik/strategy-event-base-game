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
    std::lock_guard<std::mutex> lock(mutex);
    events[event->getTarget()] = ScheduledEvent{event, runAt};
}

std::optional<std::shared_ptr<Event>> ScheduledEventQueue::pop() {
    using namespace Time;
    std::lock_guard<std::mutex> lock(mutex);
    if (events.empty()) {
        return std::nullopt;
    }

    std::optional<std::shared_ptr<Event>> scheduledEvent = std::nullopt;
    for (const auto& [event, runAt] : events | std::views::values) {
        if (runAt <= Clock::now()) {
            scheduledEvent = event;
            break;
        }
    }

    if (scheduledEvent.has_value()) {
        events.erase(scheduledEvent.value()->getTarget());
    }

    return scheduledEvent;
}

void ScheduledEventQueue::clear() {
    events.clear();
}