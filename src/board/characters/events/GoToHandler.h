#pragma once

#include "../../../events/EventHandler.h"
#include "../../../events/EventQueue.h"
#include "../../Board.h"

class GoToHandler final: public EventHandler<Character, Event> {

private:
    std::shared_ptr<Board> board;
    GoToParams             params;

protected:
    Event invoke(std::shared_ptr<Character> target) override;

public:
    explicit GoToHandler(const std::shared_ptr<Board>& board, GoToParams params);
    ~GoToHandler() override = default;
};