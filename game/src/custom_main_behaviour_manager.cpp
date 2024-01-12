#include "../include/custom_main_behaviour_manager.h"

void CustomMainBehaviourManager::init() {
    Entity2D *red_entity = this->create<Entity2D>("Red");
    Entity2D *green_entity = this->create<Entity2D>("Green");
    Entity2D *blue_entity = this->create<Entity2D>("Blue");

    this->get_engine_core()->get_entity_manager()->add_entity(red_entity);
    this->get_engine_core()->get_entity_manager()->add_entity(green_entity);
    this->get_engine_core()->get_entity_manager()->add_entity(blue_entity);

    red_entity->get_transform_component()->set_local_position(Vector2{10.0f, 0.0f});
    green_entity->get_transform_component()->set_local_position(Vector2{0.0f, 10.0f});
    blue_entity->get_transform_component()->set_local_position(Vector2{10.0f, 10.0f});
}

void CustomMainBehaviourManager::update() {}

void CustomMainBehaviourManager::exit() {}
