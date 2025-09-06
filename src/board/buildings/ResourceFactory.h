#pragma once
#include "Building.h"

class ResourceFactory final: public Building {
private:
    EconomyResource producedResource;
    int             productionAmount;

    bool serfIsComing;

public:
    ResourceFactory(BuildingType type, GridPosition position);
    ~ResourceFactory() override = default;

    [[nodiscard]] int             getProductionAmount() const { return productionAmount; }
    [[nodiscard]] EconomyResource getProducedResource() const { return producedResource; }
    void                          setSerfIsComing(const bool isComing) { serfIsComing = isComing; }
    [[nodiscard]] bool            isSerfComing() const { return serfIsComing; }
};