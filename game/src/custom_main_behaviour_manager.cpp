#include "../include/custom_main_behaviour_manager.h"

void CustomMainBehaviourManager::init() {
    this->get_engine_core()->get_entity_manager()->add_entity(new Entity("Sample"));
}

void CustomMainBehaviourManager::update() {}

void CustomMainBehaviourManager::exit() {}
