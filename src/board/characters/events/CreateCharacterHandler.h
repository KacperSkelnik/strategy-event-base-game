#pragma once

#include <utility>

#include "../../../board/Board.h"
#include "../../../events/EventHandler.h"
#include "../../../events/EventParams.h"


class CreateCharacterHandler final: public EventHandler<Board, std::optional<std::shared_ptr<Character>>> {

private:
    CreateCharacterParams params;

protected:
    std::optional<std::shared_ptr<Character>> invoke(std::shared_ptr<Board> target) override;

public:
    explicit CreateCharacterHandler(CreateCharacterParams params);
    ~CreateCharacterHandler() override = default;
};