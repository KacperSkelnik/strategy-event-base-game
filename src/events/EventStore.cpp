//
// Created by Kacper Skelnik on 15.03.2025.
//

#include "EventStore.h"

void EventStore::push(const std::shared_ptr<Event>& event) {
    events.push(event);
}

std::shared_ptr<Event> EventStore::pop() {
    std::shared_ptr<Event> event = this->events.front();
    events.pop();
    return event;
}