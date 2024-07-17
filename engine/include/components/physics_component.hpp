#pragma once

#include "../managers/physics_manager.hpp"
#include "../types.hpp"
#include "managed_component.hpp"

class PhysicsComponent : public ManagedComponent {
   public:
    PhysicsComponent(EngineCore *engine_core, Entity *entity) : ManagedComponent(engine_core, entity, true) {}
    ~PhysicsComponent() override;

   protected:
    void register_component() override;
    void unregister_component() override;
};