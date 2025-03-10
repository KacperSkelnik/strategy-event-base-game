#pragma once

class EconomyState {
  private:
    long goldAmount;

  public:
    EconomyState() = default;
    explicit EconomyState(int initialGold);
    ~EconomyState() = default;

    void               addGold(int amount);
    [[nodiscard]] bool spendGold(int amount); // iif goldAmount >= amount: true else false
    [[nodiscard]] long getGold() const;
};