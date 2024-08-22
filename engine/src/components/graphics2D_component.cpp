#include "../../include/components/graphics2D_component.hpp"

#include "../../include/engine_core.hpp"
#include "../../include/entities/entity.hpp"

Graphics2DComponent::Graphics2DComponent(EngineCore *engine_core, Entity *entity) : Component(engine_core, entity, false) {
    this->_texture = Texture2D();
    this->_source_rectangle = {0, 0, 0, 0};
    this->_destination_rectangle = {0, 0, 0, 0};
    this->_origin = {0, 0};
    this->_tint = WHITE;
    this->_rendering_mode = RenderingMode::WORLD_SPACE_2D;
    this->_layer = 0;
    this->_transform_component = this->get_entity()->get_component<Transform2DComponent>();

    this->_transform_update_listener = Transform2DComponent::TransformUpdateListener([this](Transform2DComponent *transform) {
        this->_update_origin();
        this->_rotation = transform->get_rotation();
        this->_update_destination_rectangle();
    });
}

Graphics2DComponent::~Graphics2DComponent() { this->unregister_component(); }

void Graphics2DComponent::set_texture(const Texture2D texture) {
    this->_texture = texture;
    this->_source_rectangle = {0, 0, (float)this->_texture.width, (float)this->_texture.height};
    this->_origin = {(float)this->_texture.width / 2.0f, (float)this->_texture.height / 2.0f};
    this->_update_destination_rectangle();
    this->_update_origin();
}

void Graphics2DComponent::draw() {
    DrawTexturePro(this->_texture, this->_source_rectangle, this->_destination_rectangle, this->_origin, this->_rotation, this->_tint);
}

Component *Graphics2DComponent::register_component() { return this->get_engine_core()->get_graphics_manager()->register_component(this); }

void Graphics2DComponent::unregister_component() { this->get_engine_core()->get_graphics_manager()->unregister_component(this); }

void Graphics2DComponent::_update_destination_rectangle() {
    this->_destination_rectangle = {this->_transform_component->get_position().x,
                                    this->_transform_component->get_position().y,
                                    (float)this->_texture.width * this->_transform_component->get_scale().x,
                                    (float)this->_texture.height * this->_transform_component->get_scale().y};
}

void Graphics2DComponent::_update_origin() {
    this->_origin = Vector2Multiply(Vector2{(float)this->_texture.width / 2.0f, (float)this->_texture.height / 2.0f},
                                    this->_transform_component->get_scale());
}
