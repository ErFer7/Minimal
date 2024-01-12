#include "../../include/components/graphics2D_component.h"

Graphics2DComponent::Graphics2DComponent(EngineCore *engine_core, std::string name)
    : ManagedComponent(engine_core, true, name) {
    this->_texture = nullptr;
    this->_position = {0, 0};
    this->_rotation = 0;
    this->_scale = {1, 1};
    this->_offset_position = {0, 0};
    this->_offset_rotation = 0;
    this->_offset_scale = {1, 1};
}

Graphics2DComponent::~Graphics2DComponent() {
    if (this->_texture != nullptr) {
        UnloadTexture(*this->_texture);
        delete this->_texture;
        this->_texture = nullptr;
    }
}

void Graphics2DComponent::set_texture(const Texture2D texture) {
    if (this->_texture != nullptr) {
        UnloadTexture(*this->_texture);
        delete this->_texture;
        this->_texture = nullptr;
    }

    this->_texture = new Texture2D(texture);
}

void Graphics2DComponent::on_add_to_entity() {}

void Graphics2DComponent::on_remove_from_entity() {}

void Graphics2DComponent::on_entity_parent_added(Entity *parent) {}

void Graphics2DComponent::on_entity_parent_removed(Entity *parent) {}

void Graphics2DComponent::draw() {
    DrawTexturePro(*this->_texture,
                   this->_source_rectangle,
                   this->_destination_rectangle,
                   this->_offset_position,
                   this->_offset_rotation,
                   this->_tint);
}

void Graphics2DComponent::register_component() {
    this->get_engine_core()->get_graphics_manager()->register_component(this);
}

void Graphics2DComponent::unregister_component() {
    this->get_engine_core()->get_graphics_manager()->unregister_component(this);
}
