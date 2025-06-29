//
// Created by Kacper Skelnik on 16.04.2025.
//

#include "EventLoop.h"

#include "../board/buildings/events/CreateBuildingHandler.h"
#include "../board/characters/events/CreateCharacterHandler.h"
#include "../economy/events/SpendResourceHandler.h"

EventLoop::EventLoop(const std::shared_ptr<EventQueue>& eventQueue, const std::shared_ptr<EconomyState>& economyState):
    eventQueue(eventQueue),
    economyState(economyState) {}

void EventLoop::run() const {
    auto event = eventQueue->pop();
    while (event.has_value()) {
        switch (event.value()->getEventType()) {
            case CreateBuilding: {
                constexpr int price = 50;
                if (economyState->canAfford(price)) {
                    const auto params  = event.value()->getEventParams<CreateBuildingParams>();
                    const bool success = CreateBuildingHandler(params).invokeOn(event.value()->getTarget());

                    if (success) {
                        constexpr auto spendParams = SpendResourceParams {Gold, price};
                        eventQueue->push(std::make_shared<Event>(economyState, SpendResource, spendParams));
                    }
                }
                break;
            }

            case CreateCharacter: {
                constexpr int price   = 10;
                const auto    params  = event.value()->getEventParams<CreateCharacterParams>();
                const bool    success = CreateCharacterHandler(params).invokeOn(event.value()->getTarget());

                if (success) {
                    constexpr auto spendParams = SpendResourceParams {Gold, price};
                    eventQueue->push(std::make_shared<Event>(economyState, SpendResource, spendParams));
                }
                break;
            }

            case SpendResource: {
                auto params = event.value()->getEventParams<SpendResourceParams>();
                SpendResourceHandler(params).invokeOn(event.value()->getTarget());
                break;
            }

            default: {
                break;
            }
        }
        event = eventQueue->pop();
    }
}