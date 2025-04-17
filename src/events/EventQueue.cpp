//
// Created by Kacper Skelnik on 15.03.2025.
//

#include "EventQueue.h"

void EventQueue::push(const std::shared_ptr<Event>& event) {
    eventStore.push(event);
}

std::optional<std::shared_ptr<Event>> EventQueue::front() const {
    return eventStore.front();
}

void EventQueue::pop() {
    eventStore.pop();
}