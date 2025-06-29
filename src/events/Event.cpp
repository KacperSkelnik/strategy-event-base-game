//
// Created by Kacper Skelnik on 16.04.2025.
//
#include "Event.h"

Event::Event(const std::shared_ptr<EventEntity>& target, const EventType eventType, const EventParams eventParams):
    target(target),
    eventType(eventType),
    eventParams(eventParams) {}

Event::Event(const std::shared_ptr<EventEntity>& target, const EventType eventType):
    target(target),
    eventType(eventType),
    eventParams(std::nullopt) {}