#include "../include/behaviour_component.h"

void BehaviourComponent::register_component() {
    this->get_engine_core()->get_behaviour_manager()->_register_component(this);
}

void BehaviourComponent::unregister_component() {
    this->get_engine_core()->get_behaviour_manager()->_unregister_component(this);
}