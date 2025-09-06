#pragma once

#include "../../../events/EventHandler.h"
#include "../../../events/EventQueue.h"
#include "../../Board.h"
#include "../../../economy/EconomyState.h"
#include "../SerfCharacter.h"

class StoreResourceHandler final: public EventHandler<SerfCharacter, Event> {

private:
    std::shared_ptr<Board>        board;
    std::shared_ptr<EconomyState> economyState;
    StoreResourceParams           params;

protected:
    Event invoke(std::shared_ptr<SerfCharacter> target) override;

public:
    explicit StoreResourceHandler(const std::shared_ptr<Board>&        board,
                                  const std::shared_ptr<EconomyState>& economyState,
                                  StoreResourceParams                  params);
    ~StoreResourceHandler() override = default;
};