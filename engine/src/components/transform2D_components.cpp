#include "../../include/components/transform2D_component.hpp"
#include "../../include/entities/entity.hpp"

Transform2DComponent::Transform2DComponent(EngineCore *engine_core, Entity *entity) : Component(engine_core, entity, true) {
    this->_transform_system = TransformSystem2D();
    this->_on_parent_transform_update_listener = TransformUpdateListener([this](Transform2DComponent *parent_transform) {
        this->_transform_system.set_origin(parent_transform->get_transform());
        this->_on_update_event.invoke(this);
    });

    Transform2DComponent *parent_transform = this->get_entity()->get_parent()->get_component<Transform2DComponent>();

    if (parent_transform != nullptr) {
        this->_on_parent_transform_update_listener.subscribe(parent_transform->get_on_update_event());
    }
}

void Transform2DComponent::set_relative_position(Vector2 position) {
    this->_transform_system.set_offset_position(position);
    this->_on_update_event.invoke(this);
}

void Transform2DComponent::set_relative_rotation(float rotation) {
    this->_transform_system.set_offset_rotation(rotation);
    this->_on_update_event.invoke(this);
}

void Transform2DComponent::set_relative_scale(Vector2 scale) {
    this->_transform_system.set_offset_scale(scale);
    this->_on_update_event.invoke(this);
}

void Transform2DComponent::set_relative_scale(float scale) {
    this->_transform_system.set_offset_scale(Vector2Scale(this->_transform_system.get_origin_scale(), scale));
    this->_on_update_event.invoke(this);
}

void Transform2DComponent::set_position(Vector2 position) {
    this->_transform_system.set_result_position(position);
    this->_on_update_event.invoke(this);
}

void Transform2DComponent::set_rotation(float rotation) {
    this->_transform_system.set_result_rotation(rotation);
    this->_on_update_event.invoke(this);
}

void Transform2DComponent::set_scale(Vector2 scale) {
    this->_transform_system.set_result_scale(scale);
    this->_on_update_event.invoke(this);
}

void Transform2DComponent::set_scale(float scale) {
    this->_transform_system.set_result_scale(Vector2Scale(this->_transform_system.get_origin_scale(), scale));
    this->_on_update_event.invoke(this);
}

void Transform2DComponent::translate(Vector2 translation) {
    this->_transform_system.set_offset_position(Vector2Add(this->_transform_system.get_offset_position(), translation));
    this->_on_update_event.invoke(this);
}

void Transform2DComponent::rotate(float rotation) {
    this->_transform_system.set_offset_rotation(this->_transform_system.get_offset_rotation() + rotation);
    this->_on_update_event.invoke(this);
}

void Transform2DComponent::scale(Vector2 scale) {
    this->_transform_system.set_offset_scale(Vector2Multiply(this->_transform_system.get_offset_scale(), scale));
    this->_on_update_event.invoke(this);
}

void Transform2DComponent::scale(float scale) {
    this->_transform_system.set_offset_scale(Vector2Scale(this->_transform_system.get_offset_scale(), scale));
    this->_on_update_event.invoke(this);
}
