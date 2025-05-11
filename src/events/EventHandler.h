#pragma once
#include "EventEntity.h"
#include <memory>

class IEventHandler {
  public:
    virtual ~IEventHandler()                                     = default;
    virtual void invokeBase(std::shared_ptr<EventEntity> target) = 0;
};

template <class T = EventEntity> class EventHandler: public IEventHandler {
  public:
    EventHandler()           = default;
    ~EventHandler() override = default;

    virtual void invoke(std::shared_ptr<T> target) = 0;
    void         invokeBase(const std::shared_ptr<EventEntity> target) override {
        invoke(std::static_pointer_cast<T>(target));
    };
};