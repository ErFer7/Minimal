#include "../../include/components/physics_component.h"

void PhysicsComponent::register_component() {
    this->get_engine_core()->get_physics_manager()->register_component(this);
}

void PhysicsComponent::unregister_component() {
    this->get_engine_core()->get_physics_manager()->unregister_component(this);
}