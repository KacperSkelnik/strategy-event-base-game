#pragma once

#include "../../../events/EventHandler.h"
#include "../../../events/EventParams.h"
#include "../../Board.h"
#include <memory>

class CreateBuildingHandler final: public EventHandler<Board, bool> {

private:
    CreateBuildingParams params;

protected:
    bool invoke(std::shared_ptr<Board> target) override;

public:
    explicit CreateBuildingHandler(const CreateBuildingParams& params);
    ~CreateBuildingHandler() override = default;
};