#include "../include/custom_main_behaviour_manager.hpp"
#include "../include/red_behavior.hpp"
#include "../include/green_behavior.hpp"
#include "../include/blue_behavior.hpp"

void CustomMainBehaviourManager::init() {
    this->_entity_r = this->get_engine_core()->get_entity_container()->create_entity<Entity2D>();
    this->_entity_g = this->get_engine_core()->get_entity_container()->create_entity<Entity2D>();
    this->_entity_b = this->get_engine_core()->get_entity_container()->create_entity<Entity2D>();

    this->_entity_r->get_transform_component()->set_position(Vector2{-300.0f, 0.0f});
    this->_entity_g->get_transform_component()->set_position(Vector2{0.0f, 0.0f});
    this->_entity_b->get_transform_component()->set_position(Vector2{300.0f, 0.0f});

    this->_entity_r->get_graphics_component()->set_texture(LoadTexture("runtime-test/assets/Rectangle_64.png"));
    this->_entity_g->get_graphics_component()->set_texture(LoadTexture("runtime-test/assets/Rectangle_64.png"));
    this->_entity_b->get_graphics_component()->set_texture(LoadTexture("runtime-test/assets/Rectangle_64.png"));

    this->_entity_r->get_graphics_component()->set_color(RED);
    this->_entity_g->get_graphics_component()->set_color(GREEN);
    this->_entity_b->get_graphics_component()->set_color(BLUE);

    this->_entity_r->create_component<RedBehavior>();
    this->_entity_g->create_component<GreenBehavior>();
    this->_entity_b->create_component<BlueBehavior>();
}

void CustomMainBehaviourManager::update() {
}

void CustomMainBehaviourManager::exit() {
    UnloadTexture(this->_entity_r->get_graphics_component()->get_texture());
    UnloadTexture(this->_entity_g->get_graphics_component()->get_texture());
    UnloadTexture(this->_entity_b->get_graphics_component()->get_texture());
}
