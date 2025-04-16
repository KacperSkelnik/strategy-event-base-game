//
// Created by Kacper Skelnik on 16.04.2025.
//
#include "Event.h"

Event::Event(const std::shared_ptr<EventEntity>& target, const std::shared_ptr<IEventHandler>& eventHandler):
    target(target),
    eventHandler(eventHandler) {}

void Event::execute() const {
    eventHandler->invokeBase(target);
}