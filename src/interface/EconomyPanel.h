#pragma once
#include "../EconomyState.h"
#include "EconomyCell.h"

class EconomyPanel {
  private:
    std::vector<EconomyCell> elements;
    EconomyState             economyState;

  public:
    EconomyPanel() = delete;
    explicit EconomyPanel(const EconomyState& economyState);
    ~EconomyPanel() = default;

    void update();
    void draw() const;
};