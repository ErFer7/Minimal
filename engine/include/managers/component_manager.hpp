#pragma once

#include "../types.hpp"
#include "manager.hpp"

class ComponentManager : public Manager {
   public:
    ComponentManager() = default;
    ComponentManager(EngineCore *engine_core) : Manager(engine_core){};
    ~ComponentManager() override = default;

    void update() override {};

   protected:
    virtual void register_component(Component *component) = 0;
    virtual void unregister_component(Component *component) = 0;
};
