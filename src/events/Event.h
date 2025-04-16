#pragma once
#include "EventEntity.h"
#include "EventHandler.h"
#include <memory>

class Event: std::enable_shared_from_this<Event> {
  private:
    std::shared_ptr<EventEntity>   target;
    std::shared_ptr<IEventHandler> eventHandler;

  public:
    ~Event() = default;
    Event(const std::shared_ptr<EventEntity>& target, const std::shared_ptr<IEventHandler>& eventHandler);
    void execute() const;
};