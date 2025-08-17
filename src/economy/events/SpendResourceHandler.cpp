//
// Created by Kacper Skelnik on 11.05.2025.
//

#include "SpendResourceHandler.h"

SpendResourceHandler::SpendResourceHandler(const SpendResourceParams params): params(params) {}

bool SpendResourceHandler::invoke(const std::shared_ptr<EconomyState> target) {
    bool succeeded = false;
    switch (params.resource) {
        case Gold:
            succeeded = target->trySpend(Gold, params.amount);
    }
    return succeeded;
}