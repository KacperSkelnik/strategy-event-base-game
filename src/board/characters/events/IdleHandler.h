#pragma once
#include "../../../events/Event.h"
#include "../../../events/EventHandler.h"
#include "../../Board.h"
#include "../Character.h"

class IdleHandler final: public EventHandler<Character, Event> {

private:
    std::shared_ptr<Board> board;

    [[nodiscard]] Event determineNextEvent(const std::shared_ptr<Character>& target) const;

protected:
    Event invoke(std::shared_ptr<Character> target) override;

public:
    explicit IdleHandler(const std::shared_ptr<Board>& board);
    ~IdleHandler() override = default;
};