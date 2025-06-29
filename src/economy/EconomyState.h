#pragma once

#include "../events/EventEntity.h"

class EconomyState final: public EventEntity {
  private:
    int goldAmount = 0;

  public:
    EconomyState() = delete;
    explicit EconomyState(int initialGold);
    ~EconomyState() override = default;

    void               addGold(int amount);
    [[nodiscard]] bool spendGold(int amount); // iif goldAmount >= amount: true else false
    [[nodiscard]] int  getGold() const;

    [[nodiscard]] bool canAfford(int amount) const;
};