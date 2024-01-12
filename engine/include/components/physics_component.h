#pragma once

#include "../managers/physics_manager.h"
#include "managed_component.h"

class PhysicsComponent : public ManagedComponent {
   public:
    PhysicsComponent(EngineCore *engine_core, std::string name = "") : ManagedComponent(engine_core, true, name) {}
    ~PhysicsComponent() override = default;

   protected:
    void register_component() override;
    void unregister_component() override;
};