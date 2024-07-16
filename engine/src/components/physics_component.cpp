#include "../../include/components/physics_component.hpp"

#include <cassert>

PhysicsComponent::~PhysicsComponent() {
    PhysicsManager *physics_manager = this->get_engine_core()->get_physics_manager();

    assert(physics_manager != nullptr);
    physics_manager->unregister_component(this);
}

void PhysicsComponent::register_component() { this->get_engine_core()->get_physics_manager()->register_component(this); }

void PhysicsComponent::unregister_component() { this->get_engine_core()->get_physics_manager()->unregister_component(this); }