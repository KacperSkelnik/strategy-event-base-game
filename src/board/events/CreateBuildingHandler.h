#pragma once

#include "../../events/EventHandler.h"
#include "../Board.h"
#include <memory>

class CreateBuildingHandler final: public EventHandler<Board> {
  private:
    BuildingType selectedBuilding;
    GridPosition position;

  public:
    explicit CreateBuildingHandler(BuildingType selectedBuilding, GridPosition position);
    ~CreateBuildingHandler() override = default;

    void invoke(std::shared_ptr<Board> target) override;
};