#pragma once
#include "Character.h"
#include "../../economy/EconomyResource.h"

class SerfCharacter final: public Character {

private:
    std::optional<EconomyResource> resource;
    std::optional<int>             amount;

public:
    explicit SerfCharacter(CharacterType type, GridPosition position);
    ~SerfCharacter() override = default;

    void setResource(const EconomyResource newResource, const int newAmount) {
        resource = newResource;
        amount   = newAmount;
    }

    void removeResource() {
        resource.reset();
        amount.reset();
    }

    bool                           carriesResource() const { return (resource.has_value() && amount.has_value()); }
    std::optional<EconomyResource> getResource() const { return resource; }
    std::optional<int>             getAmount() const { return amount; }
};