#pragma once

#include <cstddef>
#include <typeinfo>

#include "../utils/engine_core_dependency_injector.h"

class EngineCore;

class Manager : public EngineCoreDependencyInjector {
   public:
    Manager() = default;
    Manager(EngineCore *engine_core) : EngineCoreDependencyInjector(engine_core){};
    virtual ~Manager() = default;

    virtual void init() = 0;
    virtual void update() = 0;
    virtual void exit() = 0;
};