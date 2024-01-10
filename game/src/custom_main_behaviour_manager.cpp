#include "../include/custom_main_behaviour_manager.h"

void CustomMainBehaviourManager::init() {
    Entity *red_entity = new Entity("Red");
    Entity *green_entity = new Entity("Green");
    Entity *blue_entity = new Entity("Blue");

    this->get_engine_core()->get_entity_manager()->add_entity(red_entity);
    this->get_engine_core()->get_entity_manager()->add_entity(green_entity);
    this->get_engine_core()->get_entity_manager()->add_entity(blue_entity);
}

void CustomMainBehaviourManager::update() {}

void CustomMainBehaviourManager::exit() {}
