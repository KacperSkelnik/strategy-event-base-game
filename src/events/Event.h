#pragma once
#include "EventEntity.h"
#include "EventParams.h"
#include "EventType.h"
#include <memory>
#include <optional>
#include <variant>

class Event: std::enable_shared_from_this<Event> {
  private:
    std::shared_ptr<EventEntity> target;
    EventType                    eventType;
    std::optional<EventParams>   eventPrams;

  public:
    ~Event() = default;
    Event(const std::shared_ptr<EventEntity>& target, EventType eventType, EventParams eventPrams);
    Event(const std::shared_ptr<EventEntity>& target, EventType eventType);

    std::shared_ptr<EventEntity>                       getTarget() const { return target; }
    EventType                                          getEventType() const { return eventType; }
    template <class T> std::reference_wrapper<const T> getEventParams() const {
        if (eventPrams.has_value()) {
            const T* value = std::get_if<T>(&eventPrams.value());
            return std::cref(*value);
        }
        throw std::runtime_error("EventParams not set or type mismatch");
    }
};
