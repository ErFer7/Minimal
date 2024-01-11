#include "../../include/components/graphics2D_component.h"

Graphics2DComponent::Graphics2DComponent(std::string name) : ManagedComponent(true, name) {
    this->_texture = nullptr;
}

Graphics2DComponent::~Graphics2DComponent() {
    if (this->_texture != nullptr) {
        delete this->_texture;
        this->_texture = nullptr;
    }
}

void Graphics2DComponent::on_add_to_entity() {}

void Graphics2DComponent::on_remove_from_entity() {}

void Graphics2DComponent::on_entity_parent_added(Entity *parent) {}

void Graphics2DComponent::on_entity_parent_removed(Entity *parent) {}

void Graphics2DComponent::register_component() {
    // TODO: Fix this
    // [PTBR] Atualmente não é garantido que a engine core está registrada quando o componente é registrado
    this->get_engine_core()->get_graphics_manager()->register_component(this);
}

void Graphics2DComponent::unregister_component() {
    this->get_engine_core()->get_graphics_manager()->unregister_component(this);
}
