#pragma once

#include <cstddef>
#include <typeinfo>

#include "../utils/engine_core_dependent_injector.h"

class EngineCore;

class Manager : public EngineCoreDependentInjector {
   public:
    Manager(EngineCore *engine_core) : EngineCoreDependentInjector(engine_core){};
    virtual ~Manager() = default;

    virtual void init() = 0;
    virtual void update() = 0;
    virtual void exit() = 0;
};