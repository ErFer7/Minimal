#include "../include/custom_main_behaviour_manager.h"

void CustomMainBehaviourManager::init() {
    this->_player = this->create<Entity2D>("Player");
    this->_ground = this->create<Entity2D>("Ground");

    this->get_engine_core()->get_entity_container()->add_entity(this->_player);
    this->get_engine_core()->get_entity_container()->add_entity(this->_ground);

    this->_player->get_transform_component()->set_local_position(Vector2{100.0f, 100.0f});
    this->_ground->get_transform_component()->set_local_position(Vector2{0.0f, 0.0f});

    this->_player->get_graphics_component()->set_texture(LoadTexture("game/assets/Rectangle_64.png"));
    this->_ground->get_graphics_component()->set_texture(LoadTexture("game/assets/Rectangle_64.png"));

    this->_player->get_graphics_component()->set_color(RED);
    this->_ground->get_graphics_component()->set_color(GREEN);
}

void CustomMainBehaviourManager::update() {
    this->_player->get_transform_component()->translate(Vector2{0.2f, 0.2f});
    this->_player->get_transform_component()->rotate(0.2f);
}

void CustomMainBehaviourManager::exit() {
    UnloadTexture(*this->_player->get_graphics_component()->get_texture());
    UnloadTexture(*this->_ground->get_graphics_component()->get_texture());
}
