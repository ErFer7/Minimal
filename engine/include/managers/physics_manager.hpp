#pragma once

#include "../types.hpp"
#include "component_manager.hpp"

class PhysicsComponent;

class PhysicsManager : public ComponentManager {
   public:
    PhysicsManager() = default;
    PhysicsManager(EngineCore *engine_core) : ComponentManager(engine_core){};
    ~PhysicsManager() override = default;

    void init() override;
    void update() override;
    void exit() override;

   private:
    friend class PhysicsComponent;
};
