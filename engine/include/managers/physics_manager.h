#pragma once

#include "../components/physics_component.h"
#include "../engine_core.h"
#include "component_manager.h"

class PhysicsComponent;

class PhysicsManager : public ComponentManager {
   public:
    PhysicsManager(EngineCore *engine_core) : ComponentManager(engine_core){};
    ~PhysicsManager() override = default;
    void init() override;
    void update() override;
    void exit() override;

   private:
    friend class PhysicsComponent;
};
