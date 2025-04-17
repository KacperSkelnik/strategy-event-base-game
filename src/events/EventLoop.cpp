//
// Created by Kacper Skelnik on 16.04.2025.
//

#include "EventLoop.h"

#include <iostream>

EventLoop::EventLoop(const std::shared_ptr<EventQueue>& eventQueue): eventQueue(eventQueue) {}

void EventLoop::runSingle() const {
    if (const auto optionalEvent = eventQueue->front(); optionalEvent.has_value()) {
        const std::shared_ptr<Event>& event = optionalEvent.value();
        event->execute();
        eventQueue->pop();
    }
}