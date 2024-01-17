#include "../../include/components/graphics2D_component.h"

Graphics2DComponent::Graphics2DComponent(EngineCore *engine_core, std::string name)
    : ManagedComponent(engine_core, false, name) {
    this->_texture = new Texture2D();
    this->_transform_system = new TransformSystem2D();
    this->_source_rectangle = {0, 0, 0, 0};
    this->_destination_rectangle = {0, 0, 0, 0};
    this->_origin = {0, 0};
    this->_tint = WHITE;
    this->_rendering_mode = RenderingMode::WORLD_SPACE_2D;
    this->_layer = 0;
}

Graphics2DComponent::~Graphics2DComponent() {
    GraphicsManager *graphics_manager = this->get_engine_core()->get_graphics_manager();

    if (graphics_manager != nullptr) {
        graphics_manager->unregister_component(this);
    }

    if (this->_texture != nullptr) {
        delete this->_texture;
        this->_texture = nullptr;
    }

    if (this->_transform_system != nullptr) {
        delete this->_transform_system;
        this->_transform_system = nullptr;
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
    this->_origin = {(float)this->_texture->width / 2.0f, (float)this->_texture->height / 2.0f};
    this->_update_destination_rectangle();
    this->_update_origin();
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
                   this->_origin,
                   this->_transform_system->get_result_rotation(),
                   this->_tint);
}

void Graphics2DComponent::register_component() {
    this->get_engine_core()->get_graphics_manager()->register_component(this);
}

void Graphics2DComponent::unregister_component() {
    this->get_engine_core()->get_graphics_manager()->unregister_component(this);
}

void Graphics2DComponent::_on_transform_updated(Transform2DComponent *transform) {
    this->_transform_system->set_origin(transform->get_world_transform());
    this->_update_destination_rectangle();
    this->_update_origin();
}

void Graphics2DComponent::_update_destination_rectangle() {
    this->_destination_rectangle = {this->_transform_system->get_result_position().x,
                                    this->_transform_system->get_result_position().y,
                                    (float)this->_texture->width * this->_transform_system->get_result_scale().x,
                                    (float)this->_texture->height * this->_transform_system->get_result_scale().y};
}

void Graphics2DComponent::_update_origin() {
    this->_origin = Vector2Multiply(Vector2{(float)this->_texture->width / 2.0f, (float)this->_texture->height / 2.0f},
                                    this->_transform_system->get_result_scale());
}
