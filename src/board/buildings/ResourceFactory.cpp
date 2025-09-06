//
// Created by Kacper Skelnik on 30.06.2025.
//

#include "ResourceFactory.h"

ResourceFactory::ResourceFactory(const BuildingType type, const GridPosition position):
    Building(type, position, true),
    producedResource(getResourceProducedBy(type).value()),
    // TODO: make this configurable
    productionAmount(1) {
}
