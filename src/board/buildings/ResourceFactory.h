#pragma once
#include "Building.h"

class ResourceFactory final: public Building {
  private:
    EconomyResource producedResource;
    int             productionAmount;
    int             productionInterval;
    bool            isProducing;

  public:
    ResourceFactory(BuildingType type, GridPosition position);
    ~ResourceFactory() override = default;

    [[nodiscard]] int  getProductionAmount() const { return productionAmount; }
    [[nodiscard]] int  getProductionInterval() const { return productionInterval; }
    [[nodiscard]] bool canProduce() const { return isProducing; }
    void               startProduction() { isProducing = true; }
    void               stopProduction() { isProducing = false; }
};