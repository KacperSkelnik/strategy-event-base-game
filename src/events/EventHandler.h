#pragma once
#include "EventEntity.h"
#include <memory>

/**
 * @brief Interface for event handlers that operate on EventEntity objects.
 *
 * This class defines an interface for event handlers that can be invoked on
 * a shared pointer to an EventEntity. It is a templated interface where the
 * return type of the handler is specified via the template parameter.
 *
 * @tparam R The return type of the event handler.
 */
template <typename R> class IEventHandler {
  public:
    virtual ~IEventHandler() = default;
    /**
     * @brief Invoke the handler on the given EventEntity target.
     *
     * @param target A shared pointer to the target EventEntity.
     * @return The result of invoking the handler, of type R.
     */
    virtual R invokeOn(std::shared_ptr<EventEntity> target) = 0;
};

/**
 * @brief Base class for typed event handlers.
 *
 * This templated class extends the IEventHandler interface and provides a
 * mechanism to handle events on a specific derived type of EventEntity.
 * It uses static_pointer_cast to safely cast the EventEntity to the expected type.
 *
 * @tparam T The type of EventEntity this handler operates on. Defaults to EventEntity.
 * @tparam R The return type of the event handler. Defaults to void.
 */
template <class T = EventEntity, typename R = void> class EventHandler: public IEventHandler<R> {
  protected:
    virtual R invoke(std::shared_ptr<T> target) = 0;

  public:
    EventHandler()           = default;
    ~EventHandler() override = default;

    /**
     * @brief Invoke the handler on a generic EventEntity.
     *
     * This method casts the EventEntity to the expected type T and
     * forwards the call to the typed invoke method.
     *
     * @param target A shared pointer to the target EventEntity.
     * @return The result of invoking the handler, of type R.
     */
    R invokeOn(const std::shared_ptr<EventEntity> target) override {
        return invoke(std::static_pointer_cast<T>(target));
    }
};