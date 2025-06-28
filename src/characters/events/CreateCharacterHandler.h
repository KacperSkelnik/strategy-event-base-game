#pragma once

#include "../../events/EventHandler.h"
#include "../Character.h"

class CreateCharacterHandler final: public EventHandler<Character> {
  private:
    int myVariable;

  public:
    explicit CreateCharacterHandler();
    ~CreateCharacterHandler() override = default;

    void invoke(std::shared_ptr<Character> target) override;
};