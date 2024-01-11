#include "../include/custom_main_behaviour_manager.h"

void CustomMainBehaviourManager::init() {
    Entity2D *red_entity = new Entity2D("Red");
    Entity2D *green_entity = new Entity2D("Green");
    Entity2D *blue_entity = new Entity2D("Blue");

    this->get_engine_core()->get_entity_manager()->add_entity(red_entity);
    this->get_engine_core()->get_entity_manager()->add_entity(green_entity);
    this->get_engine_core()->get_entity_manager()->add_entity(blue_entity);
}

void CustomMainBehaviourManager::update() {}

void CustomMainBehaviourManager::exit() {}
