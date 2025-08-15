#pragma once

#include "../../events/EventHandler.h"
#include "../../events/EventParams.h"
#include "../EconomyState.h"

class SpendResourceHandler final: public EventHandler<EconomyState, bool> {

private:
    SpendResourceParams params;

protected:
    bool invoke(std::shared_ptr<EconomyState> target) override;

public:
    explicit SpendResourceHandler(SpendResourceParams params);
    ~SpendResourceHandler() override = default;
};