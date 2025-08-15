#pragma once

#include "../../../events/EventHandler.h"
#include "../../../events/EventQueue.h"
#include "../../Board.h"
#include "../SerfCharacter.h"

class GoForResourceHandler final: public EventHandler<SerfCharacter, Event> {

private:
    std::shared_ptr<Board> board;
    GoForResourceParams    params;

protected:
    Event invoke(std::shared_ptr<SerfCharacter> target) override;

public:
    explicit GoForResourceHandler(const std::shared_ptr<Board>& board, const GoForResourceParams& params);
    ~GoForResourceHandler() override = default;
};