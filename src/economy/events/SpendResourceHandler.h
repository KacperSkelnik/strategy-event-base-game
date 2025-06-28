#pragma once

#include "../../events/EventHandler.h"
#include "../../events/EventParams.h"
#include "../EconomyResource.h"
#include "../EconomyState.h"

class SpendResourceHandler final: public EventHandler<EconomyState> {
  private:
    SpendResourceParams params;

  public:
    explicit SpendResourceHandler(SpendResourceParams params);
    ~SpendResourceHandler() override = default;

    void invoke(std::shared_ptr<EconomyState> target) override;
};