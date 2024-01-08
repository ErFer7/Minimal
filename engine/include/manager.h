#pragma once

#include <cstddef>
#include <typeinfo>

#include "engine_core.h"
#include "component.h"

class EngineCore;

class Component;

class Manager {
   public:
    Manager(EngineCore *engine_core) : _engine_core(engine_core) {}
    virtual ~Manager() = default;
    virtual void init() = 0;
    virtual void update() = 0;
    virtual void exit() = 0;
    inline EngineCore *get_engine_core() { return this->_engine_core; }

   private:
    EngineCore *_engine_core;
};