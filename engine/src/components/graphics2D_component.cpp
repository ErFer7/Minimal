#include "../../include/components/graphics2D_component.h"

Graphics2DComponent::Graphics2DComponent(EngineCore *engine_core, std::string name)
    : ManagedComponent(engine_core, false, name) {
    this->_texture = nullptr;
    this->_origin_position = {0, 0};
    this->_origin_rotation = 0;
    this->_origin_scale = {1, 1};
    this->_screen_position = {0, 0};
    this->_screen_rotation = 0;
    this->_screen_scale = {1, 1};
    this->_offset_position = {0, 0};
    this->_offset_rotation = 0;
    this->_offset_scale = {1, 1};
    this->_source_rectangle = {0, 0, 0, 0};
    this->_destination_rectangle = {0, 0, 0, 0};
    this->_tint = WHITE;
}

Graphics2DComponent::~Graphics2DComponent() {
    if (this->_texture != nullptr) {
        delete this->_texture;
        this->_texture = nullptr;
    }

    if (this->_update_transform_callback != nullptr) {
        delete this->_update_transform_callback;
        this->_update_transform_callback = nullptr;
    }
}

void Graphics2DComponent::set_texture(const Texture2D texture) {
    if (this->_texture != nullptr) {
        delete this->_texture;
        this->_texture = nullptr;
    }

    this->_texture = new Texture2D(texture);
    this->_source_rectangle = {0, 0, (float)this->_texture->width, (float)this->_texture->height};
    this->_destination_rectangle = {this->_origin_position.x, this->_origin_position.y, (float)this->_texture->width, (float)this->_texture->height};
}

void Graphics2DComponent::on_add_to_entity() {
    Transform2DComponent *transform = this->get_entity()->get_component<Transform2DComponent>();

    if (transform != nullptr) {
        this->_update_transform_callback = new std::function<void(Transform2DComponent *)>(
            [this](Transform2DComponent *transform) { this->_on_transform_updated(transform); });

        transform->add_update_callback(this->_update_transform_callback);
        this->_on_transform_updated(transform);
    }
}

void Graphics2DComponent::on_remove_from_entity() {
    Transform2DComponent *transform = this->get_entity()->get_component<Transform2DComponent>();

    if (transform != nullptr) {
        transform->remove_update_callback(this->_update_transform_callback);
    }
}

void Graphics2DComponent::on_entity_parent_added(Entity *parent) {}

void Graphics2DComponent::on_entity_parent_removed(Entity *parent) {}

void Graphics2DComponent::draw() {
    DrawTexturePro(*this->_texture,
                   this->_source_rectangle,
                   this->_destination_rectangle,
                   this->_origin_position,
                   this->_origin_rotation,
                   this->_tint);
}

void Graphics2DComponent::register_component() {
    this->get_engine_core()->get_graphics_manager()->register_component(this);
}

void Graphics2DComponent::unregister_component() {
    this->get_engine_core()->get_graphics_manager()->unregister_component(this);
}

void Graphics2DComponent::_on_transform_updated(Transform2DComponent *transform) {
    this->_origin_position = transform->get_world_position();
    this->_origin_rotation = transform->get_world_rotation();
    this->_origin_scale = transform->get_world_scale();

    if (this->_texture != nullptr) {
        this->_destination_rectangle.x = this->_origin_position.x / 2.0f;
        this->_destination_rectangle.y = this->_origin_position.y / 2.0f;
        this->_destination_rectangle.width = this->_texture->width * this->_origin_scale.x;
        this->_destination_rectangle.height = this->_texture->height * this->_origin_scale.y;
    }
}
