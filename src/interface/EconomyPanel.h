#pragma once
#include "../economy/EconomyState.h"
#include "EconomyCell.h"

class EconomyPanel {
  private:
    std::vector<EconomyCell>      elements;
    std::shared_ptr<EconomyState> economyState;

  public:
    EconomyPanel() = delete;
    explicit EconomyPanel(std::shared_ptr<EconomyState> economyState);
    ~EconomyPanel() = default;

    void update();
    void draw() const;
};