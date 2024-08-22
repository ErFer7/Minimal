#include "../../include/components/transform2D_component.hpp"
#include "../../include/entities/entity.hpp"

Transform2DComponent::Transform2DComponent(EngineCore *engine_core, Entity *entity) : Component(engine_core, entity, true) {
    this->_transform_system = TransformSystem2D();
    this->_on_parent_transform_update_listener = TransformUpdateListener([this](Transform2DComponent *parent_transform) {
        Transform2D relative = this->get_relative_transform();
        this->_transform_system.set_relative(parent_transform->get_transform(), relative);
        this->_on_update_event.invoke(this);
    });

    this->_parent_transform = this->get_entity()->get_parent()->get_component<Transform2DComponent>();
    this->_on_parent_transform_update_listener.subscribe(this->_parent_transform->get_on_update_event());
}

void Transform2DComponent::set_position(Vector2 position) {
    this->_transform_system.set_absolute_position(position);
    this->_on_update_event.invoke(this);
}

void Transform2DComponent::set_rotation(float rotation) {
    this->_transform_system.set_absolute_rotation(rotation);
    this->_on_update_event.invoke(this);
}

void Transform2DComponent::set_scale(Vector2 scale) {
    this->_transform_system.set_absolute_scale(scale);
    this->_on_update_event.invoke(this);
}

void Transform2DComponent::set_relative_position(Vector2 position) {
    this->_transform_system.set_relative_position(this->_parent_transform->get_position(), position);
    this->_on_update_event.invoke(this);
}

void Transform2DComponent::set_relative_rotation(float rotation) {
    this->_transform_system.set_relative_rotation(this->_parent_transform->get_rotation(), rotation);
    this->_on_update_event.invoke(this);
}

void Transform2DComponent::set_relative_scale(Vector2 scale) {
    this->_transform_system.set_relative_scale(this->_parent_transform->get_scale(), scale);
    this->_on_update_event.invoke(this);
}

void Transform2DComponent::translate(Vector2 translation) {
    this->_transform_system.translate(translation);
    this->_on_update_event.invoke(this);
}

void Transform2DComponent::rotate(float rotation) {
    this->_transform_system.rotate(rotation);
    this->_on_update_event.invoke(this);
}

void Transform2DComponent::scale(Vector2 scale) {
    this->_transform_system.scale(scale);
    this->_on_update_event.invoke(this);
}
