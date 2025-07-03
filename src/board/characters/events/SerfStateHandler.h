#pragma once
#include "../../../events/EventQueue.h"
#include "../../../events/EventHandler.h"
#include "../Character.h"


class SerfStateHandler final: public EventHandler<Character> {
  private:
    std::shared_ptr<EventQueue> eventQueue;

  public:
    explicit SerfStateHandler();
    ~SerfStateHandler() override = default;

    void invoke(std::shared_ptr<Character> target) override;
};