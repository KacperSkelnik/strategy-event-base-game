#pragma once
#include "Building.h"
#include "Grid.h"
#include <vector>

class Board final: public EventEntity {
  private:
    std::vector<std::shared_ptr<Building>> buildings;
    std::shared_ptr<Grid>                  grid;

  public:
    explicit Board(std::shared_ptr<Grid> grid);
    ~Board() override = default;

    bool                                     createBuilding(BuildingType buildingType, const sf::Vector2i& position);
    std::optional<std::shared_ptr<Building>> trySelectBuilding(const sf::Vector2i& mousePosition) const;
};