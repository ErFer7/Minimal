#pragma once

#include "../managers/physics_manager.hpp"
#include "../types.hpp"
#include "component.hpp"

class PhysicsComponent : public Component {
   public:
    PhysicsComponent(EngineCore *engine_core, Entity *entity) : Component(engine_core, entity, true) {}
    ~PhysicsComponent() override;

   protected:
    void register_component() override;
    void unregister_component() override;
};