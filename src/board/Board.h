#pragma once
#include "../interface/Grid.h"
#include "Building.h"
#include <vector>

class Board final: public EventEntity {
  private:
    std::vector<std::shared_ptr<Building>> buildings;
    std::shared_ptr<Grid>                  grid;

  public:
    explicit Board(const std::shared_ptr<Grid>& grid);
    ~Board() override = default;

    void createBuilding(BuildingType buildingType, const sf::Vector2i& position);
};