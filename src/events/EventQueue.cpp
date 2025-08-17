//
// Created by Kacper Skelnik on 15.03.2025.
//

#include "EventQueue.h"

EventQueue::EventQueue(): events(std::map<std::shared_ptr<EventEntity>, std::shared_ptr<Event>>()) {
}

void EventQueue::push(const std::shared_ptr<Event>& event) {
    events[event->getTarget()] = event;
}

std::optional<std::shared_ptr<Event>> EventQueue::pop() {
    if (events.empty()) {
        return std::nullopt;
    }
    auto [key, event] = *events.begin();
    events.erase(key);
    return event;
}

void EventQueue::clear() {
    events.clear();
}