#pragma once

#include "../../../board/Board.h"
#include "../../../events/EventHandler.h"
#include "../../../events/EventParams.h"

class CreateCharacterHandler final: public EventHandler<Board, bool> {
  private:
    CreateCharacterParams params;

  protected:
    bool invoke(std::shared_ptr<Board> target) override;

  public:
    explicit CreateCharacterHandler(const CreateCharacterParams& params);
    ~CreateCharacterHandler() override = default;
};