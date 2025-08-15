//
// Created by Kacper Skelnik on 30.06.2025.
//

#include "ResourceFactory.h"

ResourceFactory::ResourceFactory(const BuildingType type, const GridPosition position):
    Building(type, position, true),
    producedResource(getProducedResource(type).value()), // It has to be a valid resource for the factory type
    productionAmount(1),                                 // TODO: make this configurable
    productionInterval(10),                              // TODO: make this configurable
    isProducing(false) {}