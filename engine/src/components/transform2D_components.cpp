#include "../../include/components/transform2D_component.h"

Transform2DComponent::Transform2DComponent(std::string name) : Component(true, name) {
    this->_local_position = Vector2Zero();
    this->_local_rotation = 0.0f;
    this->_local_scale = Vector2One();
    this->_world_position = Vector2Zero();
    this->_world_rotation = 0.0f;
    this->_world_scale = Vector2One();
    this->_origin_position = Vector2Zero();
    this->_origin_rotation = 0.0f;
    this->_origin_scale = Vector2One();
    this->_update_callbacks = new DynamicArray<std::function<void(Transform2DComponent *)> *>();
}

Transform2DComponent::~Transform2DComponent() {
    if (this->_update_callbacks != nullptr) {
        for (unsigned int i = 0; i < this->_update_callbacks->get_size(); i++) {
            std::function<void(Transform2DComponent *)> *callback = this->_update_callbacks->nullable_at(i);

            if (callback != nullptr) {
                delete callback;
                this->_update_callbacks->nullable_remove_at(i, false);
            }
        }

        this->_update_callbacks->clear();
        delete this->_update_callbacks;
        this->_update_callbacks = nullptr;
    }
}

void Transform2DComponent::on_add_to_entity() {
    Transform2DComponent *parent_transform = this->get_entity()->get_component<Transform2DComponent>();

    if (parent_transform == nullptr) {
        return;
    }

    parent_transform->add_update_callback(new std::function<void(Transform2DComponent *)>(
        [this](Transform2DComponent *parent_transform) { this->_on_parent_transform_updated(parent_transform); }));

    this->_origin_position = parent_transform->get_world_position();
    this->_origin_rotation = parent_transform->get_world_rotation();
    this->_origin_scale = parent_transform->get_world_scale();

    this->_update_world_position();
    this->_update_world_rotation();
    this->_update_world_scale();

    this->_notify_update();
}

void Transform2DComponent::on_remove_from_entity() {
    Transform2DComponent *parent_transform = this->get_entity()->get_component<Transform2DComponent>();

    if (parent_transform == nullptr) {
        return;
    }

    parent_transform->remove_update_callback(new std::function<void(Transform2DComponent *)>(
        [this](Transform2DComponent *parent_transform) { this->_on_parent_transform_updated(parent_transform); }));
}

void Transform2DComponent::set_local_position(Vector2 position) {
    this->_local_position = position;

    this->_update_world_position();
    this->_notify_update();
}

void Transform2DComponent::set_local_rotation(float rotation) {
    this->_local_rotation = rotation;

    this->_update_world_rotation();
    this->_notify_update();
}

void Transform2DComponent::set_local_scale(Vector2 scale) {
    this->_local_scale = scale;

    this->_update_world_scale();
    this->_notify_update();
}

void Transform2DComponent::set_local_scale(float scale) {
    this->_local_scale = Vector2Scale(this->_origin_scale, scale);

    this->_update_world_scale();
    this->_notify_update();
}

void Transform2DComponent::set_world_position(Vector2 position) {
    Vector2 difference = Vector2Subtract(position, this->_origin_position);
    this->_local_position = Vector2Add(this->_local_position, difference);

    this->_update_world_position();
    this->_notify_update();
}

void Transform2DComponent::set_world_rotation(float rotation) {
    this->_local_rotation += rotation - this->_origin_rotation;

    this->_update_world_rotation();
    this->_notify_update();
}

void Transform2DComponent::set_world_scale(Vector2 scale) {
    Vector2 difference = Vector2Divide(scale, this->_origin_scale);
    this->_local_scale = Vector2Multiply(this->_local_scale, difference);

    this->_update_world_scale();
    this->_notify_update();
}

void Transform2DComponent::set_world_scale(float scale) {
    Vector2 vector_scale = Vector2Scale(this->_origin_scale, scale);
    Vector2 difference = Vector2Divide(vector_scale, this->_origin_scale);
    this->_local_scale = Vector2Multiply(this->_local_scale, difference);

    this->_update_world_scale();
    this->_notify_update();
}

void Transform2DComponent::translate(Vector2 translation) {
    this->_local_position = Vector2Add(this->_local_position, translation);

    this->_update_world_position();
    this->_notify_update();
}

void Transform2DComponent::rotate(float rotation) {
    this->_local_rotation += rotation;

    this->_update_world_rotation();
    this->_notify_update();
}

void Transform2DComponent::scale(Vector2 scale) {
    this->_local_scale = Vector2Multiply(this->_local_scale, scale);

    this->_update_world_scale();
    this->_notify_update();
}

void Transform2DComponent::scale(float scale) {
    this->_local_scale = Vector2Scale(this->_local_scale, scale);

    this->_update_world_scale();
    this->_notify_update();
}

void Transform2DComponent::_update_world_position() {
    this->_world_position = Vector2Add(this->_local_position, this->_origin_position);
}

void Transform2DComponent::_update_world_rotation() {
    this->_world_rotation = this->_local_rotation + this->_origin_rotation;
}

void Transform2DComponent::_update_world_scale() {
    this->_world_scale = Vector2Multiply(this->_local_scale, this->_origin_scale);
}

void Transform2DComponent::_notify_update() {
    for (unsigned int i = 0; i < this->_update_callbacks->get_size(); i++) {
        std::function<void(Transform2DComponent *)> *callback = this->_update_callbacks->nullable_at(i);

        if (callback != nullptr) {
            callback->operator()(this);
        }
    }
}

void Transform2DComponent::_on_parent_transform_updated(Transform2DComponent *parent_transform) {
    this->_origin_position = parent_transform->get_world_position();
    this->_origin_rotation = parent_transform->get_world_rotation();
    this->_origin_scale = parent_transform->get_world_scale();

    this->_update_world_position();
    this->_update_world_rotation();
    this->_update_world_scale();

    this->_notify_update();
}
