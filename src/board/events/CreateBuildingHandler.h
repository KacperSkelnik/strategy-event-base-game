#pragma once

#include "../../events/EventHandler.h"
#include "../../events/EventParams.h"
#include "../Board.h"
#include <memory>

class CreateBuildingHandler final: public EventHandler<Board> {
  private:
    CreateBuildingParams params;

  public:
    explicit CreateBuildingHandler(const CreateBuildingParams& params);
    ~CreateBuildingHandler() override = default;

    void invoke(std::shared_ptr<Board> target) override;
};