#pragma once

#include "../../events/EventHandler.h"
#include "../EconomyResource.h";
#include "../EconomyState.h";

class SpendResourceHandler final: public EventHandler<EconomyState> {
  private:
    EconomyResource resource;
    int             amount;

  public:
    explicit SpendResourceHandler(EconomyResource resource, int amount);
    ~SpendResourceHandler() override = default;

    void invoke(std::shared_ptr<EconomyState> target) override;
};