#include "../../include/components/behaviour_component.h"

BehaviourComponent::~BehaviourComponent() {
    BehaviourManager *behaviour_manager = this->get_engine_core()->get_behaviour_manager();

    if (behaviour_manager != nullptr) {
        behaviour_manager->unregister_component(this);
    }
}

void BehaviourComponent::register_component() {
    this->get_engine_core()->get_behaviour_manager()->register_component(this);
}

void BehaviourComponent::unregister_component() {
    this->get_engine_core()->get_behaviour_manager()->unregister_component(this);
}