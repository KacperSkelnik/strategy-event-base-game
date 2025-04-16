#pragma once
#include "Building.h"
#include <vector>

class Board final: public EventEntity {
  private:
    std::vector<std::shared_ptr<Building>> buildings;

  public:
    Board();
    ~Board() override = default;

    void createBuilding(const std::shared_ptr<Building>& building);
};