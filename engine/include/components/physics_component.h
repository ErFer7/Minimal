#pragma once

#include "../managers/physics_manager.h"
#include "component.h"

class PhysicsComponent : public Component {
   public:
    PhysicsComponent(std::string name = "") : Component(true, name) {}
    ~PhysicsComponent() override = default;
    void on_init() override;
    void on_update() override;
    void on_exit() override;

   protected:
    void register_component() override;
    void unregister_component() override;
};