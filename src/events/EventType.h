#pragma once

enum EventType {
    // Roads
    CreateRoad,
    // Buildings
    CreateBuilding,
    // Characters
    CreateCharacter,
    // Characters - behavioral
    Idle,
    // For Serfs
    GoForResource,
    StoreResource,
    // For Workers
    GoToWork,
    Work,
    // Universal
    GoEat,
    Eat,
    // Economy
    SpendResource,
    ProduceResource,
    //
    GoTo
};
