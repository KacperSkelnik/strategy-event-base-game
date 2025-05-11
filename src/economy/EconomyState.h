#pragma once

#include "../events/EventEntity.h"

class EconomyState final: public EventEntity {
  private:
    long goldAmount = 0;

  public:
    EconomyState() = delete;
    explicit EconomyState(long initialGold);
    ~EconomyState() override = default;

    void               addGold(long amount);
    [[nodiscard]] bool spendGold(long amount); // iif goldAmount >= amount: true else false
    [[nodiscard]] long getGold() const;
};