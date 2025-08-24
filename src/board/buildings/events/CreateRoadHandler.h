#pragma once

#include "../../../events/EventHandler.h"
#include "../../../events/EventParams.h"
#include "../../Board.h"
#include <memory>

class CreateRoadHandler final: public EventHandler<Board, bool> {

private:
    CreateRoadParams params;

protected:
    bool invoke(std::shared_ptr<Board> target) override;

public:
    explicit CreateRoadHandler(const CreateRoadParams& params);
    ~CreateRoadHandler() override = default;
};