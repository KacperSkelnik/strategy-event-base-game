#pragma once

#include "../events/EventEntity.h"

class Character final: public EventEntity {
  private:
    int myVariable;

  public:
    Character();
    ~Character() override = default;

    void myMethod() const;
};