#pragma once
#include "../EconomyState.h"
#include "EconomyCell.h"
#include "SFML/Graphics/RectangleShape.hpp"

class EconomyPanel {
  private:
    std::vector<EconomyCell> elements;
    EconomyState             economyState;

  public:
    EconomyPanel() = delete;
    explicit EconomyPanel(const EconomyState& economyState);
    ~EconomyPanel() = default;

    void draw() const;
};