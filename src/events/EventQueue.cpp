//
// Created by Kacper Skelnik on 15.03.2025.
//

#include "EventQueue.h"

void EventQueue::enqueue(const std::shared_ptr<Event>& event) {
    eventQueue.push(event);
}