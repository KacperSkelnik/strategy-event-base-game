//
// Created by Kacper Skelnik on 16.04.2025.
//
#include "Event.h"

Event::Event(const std::shared_ptr<EventEntity>& target, const EventType eventType, const EventParams eventPrams):
    target(target),
    eventType(eventType),
    eventPrams(eventPrams) {}

Event::Event(const std::shared_ptr<EventEntity>& target, const EventType eventType):
    target(target),
    eventType(eventType),
    eventPrams(std::nullopt) {}

std::shared_ptr<EventEntity> Event::getTarget() const {
    return target;
}

EventType Event::getEventType() const {
    return eventType;
}

template <class T> std::reference_wrapper<const T> Event::getEventParams() const {
    if (eventPrams.has_value()) {
        const T* value = std::get_if<T>(&eventPrams.value());
        return std::cref(*value);
    }
}

template std::reference_wrapper<const CreateBuildingParams> Event::getEventParams<CreateBuildingParams>() const;
template std::reference_wrapper<const SpendResourceParams>  Event::getEventParams<SpendResourceParams>() const;