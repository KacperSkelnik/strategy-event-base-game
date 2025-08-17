#pragma once

#include "../events/EventEntity.h"
#include "EconomyResource.h"
#include <unordered_map>

class EconomyState final: public EventEntity {

private:
    std::unordered_map<EconomyResource, int> resources;

public:
    explicit EconomyState(int initialGold);
    ~EconomyState() override = default;

    void               add(EconomyResource type, int amount);
    [[nodiscard]] bool trySpend(EconomyResource type, int amount);
    [[nodiscard]] int  getResourceAmount(EconomyResource type) const;
    [[nodiscard]] bool canAfford(EconomyResource type, int amount) const;
};