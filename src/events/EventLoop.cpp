//
// Created by Kacper Skelnik on 16.04.2025.
//

#include "EventLoop.h"

#include "../board/events/CreateBuildingHandler.h"
#include "../economy/events/SpendResourceHandler.h"

EventLoop::EventLoop(const std::shared_ptr<EventQueue>& eventQueue, const std::shared_ptr<EconomyState>& economyState):
    eventQueue(eventQueue),
    economyState(economyState) {}

void EventLoop::run() const {
    auto event = eventQueue->pop();
    while (event.has_value()) {
        switch (event.value()->getEventType()) {
            case CreateBuilding: {
                auto params = event.value()->getEventParams<CreateBuildingParams>();
                CreateBuildingHandler(params).invokeBase(event.value()->getTarget());

                auto spendParams = SpendResourceParams {Gold, 50};
                eventQueue->push(std::make_shared<Event>(economyState, SpendResource, spendParams));
                break;
            }

            case SpendResource: {
                auto params = event.value()->getEventParams<SpendResourceParams>();
                SpendResourceHandler(params).invokeBase(event.value()->getTarget());
                break;
            }

            default: {
                break;
            }
        }
        event = eventQueue->pop();
    }
}