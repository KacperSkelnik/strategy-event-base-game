#pragma once

#include "../../events/EventHandler.h"
#include "../Board.h"
#include <memory>

class CreateBuildingHandler final: public EventHandler<Board> {
  private:
    BuildingType selectedBuilding;
    sf::Vector2i position;

  public:
    explicit CreateBuildingHandler(BuildingType selectedBuilding, const sf::Vector2i& position);
    ~CreateBuildingHandler() override = default;

    void invoke(std::shared_ptr<Board> target) override;
};