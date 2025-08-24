//
// Created by Kacper Skelnik on 16.04.2025.
//

#include "EventLoop.h"

#include "ScheduledEventQueue.h"
#include "../board/buildings/events/CreateBuildingHandler.h"
#include "../board/buildings/events/CreateRoadHandler.h"
#include "../board/characters/events/CreateCharacterHandler.h"
#include "../board/characters/events/GoForResourceHandler.h"
#include "../board/characters/events/StoreResourceHandler.h"
#include "../board/characters/events/IdleHandler.h"
#include "../economy/events/SpendResourceHandler.h"
#include "../globals/Time.h"
#include "../globals/Settings.h"

EventLoop::EventLoop(
    const std::shared_ptr<EventQueue>&          eventQueue,
    const std::shared_ptr<ScheduledEventQueue>& scheduledEventQueue,
    const std::shared_ptr<EconomyState>&        economyState,
    const std::shared_ptr<Board>&               board
):
    eventQueue(eventQueue),
    scheduledEventQueue(scheduledEventQueue),
    economyState(economyState),
    board(board) {
}

void EventLoop::applyEvent(const std::shared_ptr<Event>& event) const {
    switch (event->getEventType()) {
        case CreateRoad: {
            // TODO: Make the price configurable
            constexpr int price = 5;
            if (economyState->canAfford(Gold, price)) {
                const auto params  = event->getEventParams<CreateRoadParams>();
                const bool success = CreateRoadHandler(params).invokeOn(event->getTarget());

                if (success) {
                    constexpr auto spendParams = SpendResourceParams{Gold, price};
                    eventQueue->push(std::make_shared<Event>(economyState, SpendResource, spendParams));
                }
            }
            break;
        }

        case CreateBuilding: {
            // TODO: Make the price configurable
            constexpr int price = 50;
            if (economyState->canAfford(Gold, price)) {
                const auto params  = event->getEventParams<CreateBuildingParams>();
                const bool success = CreateBuildingHandler(params).invokeOn(event->getTarget());

                if (success) {
                    constexpr auto spendParams = SpendResourceParams{Gold, price};
                    eventQueue->push(std::make_shared<Event>(economyState, SpendResource, spendParams));
                }
            }
            break;
        }

        case CreateCharacter: {
            // TODO: Make the price configurable
            constexpr int price = 10;
            if (!economyState->canAfford(Gold, price)) {
                break;
            }

            const auto params = event->getEventParams<CreateCharacterParams>();
            switch (params.get().characterType) {
                case Serf: {
                    auto createdCharacter = CreateCharacterHandler(params).invokeOn(
                        event->getTarget());
                    if (!createdCharacter.has_value()) {
                        break;
                    }
                    eventQueue->push(std::make_shared<Event>(createdCharacter.value(), Idle));
                }
                default: {
                    break;
                }
            }

            constexpr auto spendParams = SpendResourceParams{Gold, price};
            eventQueue->push(std::make_shared<Event>(economyState, SpendResource, spendParams));
            break;
        }

        case SpendResource: {
            auto params = event->getEventParams<SpendResourceParams>();
            SpendResourceHandler(params).invokeOn(event->getTarget());
            break;
        }

        case Idle: {
            // This is the case when a character waits for the next action. The IdleHandler should decide what to do next.
            using namespace Time;
            using namespace Settings;

            auto           handler   = IdleHandler(board);
            Event          nextEvent = handler.invokeOn(event->getTarget());
            const sf::Time runAt     = Clock::now() + Variables::getClockTickDuration();
            scheduledEventQueue->push(std::make_shared<Event>(nextEvent), runAt);
            break;
        }

        case GoForResource: {
            using namespace Time;
            using namespace Settings;

            const auto     params    = event->getEventParams<GoForResourceParams>();
            auto           handler   = GoForResourceHandler(board, params);
            Event          nextEvent = handler.invokeOn(event->getTarget());
            const sf::Time runAt     = Clock::now() + Variables::getClockTickDuration();
            scheduledEventQueue->push(std::make_shared<Event>(nextEvent), runAt);
            break;
        }

        case StoreResource: {
            using namespace Time;
            using namespace Settings;

            const auto     params    = event->getEventParams<StoreResourceParams>();
            auto           handler   = StoreResourceHandler(board, economyState, params);
            Event          nextEvent = handler.invokeOn(event->getTarget());
            const sf::Time runAt     = Clock::now() + Variables::getClockTickDuration();
            scheduledEventQueue->push(std::make_shared<Event>(nextEvent), runAt);
            break;
        }

        default: {
            break;
        }
    }
}

void EventLoop::drain() const {

    while (!eventQueue->empty()) {
        const auto event = eventQueue->pop();
        if (event.has_value()) {
            applyEvent(event.value());
        }
    }

    for (const auto ready : scheduledEventQueue->popReady()) {
        applyEvent(ready);
    }
}

void EventLoop::stop() const {
    eventQueue->clear();
    scheduledEventQueue->clear();
}