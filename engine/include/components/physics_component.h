#pragma once

#include "../managers/physics_manager.h"
#include "managed_component.h"

class PhysicsComponent : public ManagedComponent {
   public:
    PhysicsComponent(std::string name = "") : ManagedComponent(true, name) {}
    ~PhysicsComponent() override = default;

   protected:
    void register_component() override;
    void unregister_component() override;
};