#include "../../include/components/transform2D_component.hpp"

Transform2DComponent::Transform2DComponent(EngineCore *engine_core, Entity *entity) : Component(engine_core, entity, true) {
    this->_transform_system = new TransformSystem2D();
    this->_update_origin_callback = nullptr;
    this->_update_callbacks = new DynamicArray<std::function<void(Transform2DComponent *)> *>();
}

Transform2DComponent::~Transform2DComponent() {
    if (this->_update_origin_callback != nullptr) {
        delete this->_update_origin_callback;
        this->_update_origin_callback = nullptr;
    }

    if (this->_transform_system != nullptr) {
        delete this->_transform_system;
        this->_transform_system = nullptr;
    }

    if (this->_update_callbacks != nullptr) {
        this->_update_callbacks->clear();
        delete this->_update_callbacks;
        this->_update_callbacks = nullptr;
    }
}

void Transform2DComponent::on_entity_parent_added(Entity *parent) {
    Transform2DComponent *parent_transform = parent->get_component<Transform2DComponent>();

    if (parent_transform != nullptr) {
        this->_update_origin_callback = new std::function<void(Transform2DComponent *)>(
            [this](Transform2DComponent *parent_transform) { this->_on_parent_transform_updated(parent_transform); });

        parent_transform->add_update_callback(this->_update_origin_callback);
        this->_on_parent_transform_updated(parent_transform);
    }
}

void Transform2DComponent::on_entity_parent_removed(Entity *parent) {
    Transform2DComponent *parent_transform = parent->get_component<Transform2DComponent>();

    if (parent_transform != nullptr) {
        parent_transform->remove_update_callback(this->_update_origin_callback);
    }
}

void Transform2DComponent::on_add_to_entity() {
    Entity *parent = this->get_entity()->get_parent();

    if (parent != nullptr) {
        Transform2DComponent *parent_transform = parent->get_component<Transform2DComponent>();

        if (parent_transform != nullptr) {
            this->_update_origin_callback = new std::function<void(Transform2DComponent *)>(
                [this](Transform2DComponent *parent_transform) { this->_on_parent_transform_updated(parent_transform); });

            parent_transform->add_update_callback(this->_update_origin_callback);
            this->_on_parent_transform_updated(parent_transform);
        }
    }
}

void Transform2DComponent::on_remove_from_entity() {
    Entity *parent = this->get_entity()->get_parent();
    if (parent != nullptr) {
        Transform2DComponent *parent_transform = parent->get_component<Transform2DComponent>();

        if (parent_transform != nullptr) {
            parent_transform->remove_update_callback(this->_update_origin_callback);
        }
    }
}

void Transform2DComponent::set_local_position(Vector2 position) {
    this->_transform_system->set_offset_position(position);
    this->_notify_update();
}

void Transform2DComponent::set_local_rotation(float rotation) {
    this->_transform_system->set_offset_rotation(rotation);
    this->_notify_update();
}

void Transform2DComponent::set_local_scale(Vector2 scale) {
    this->_transform_system->set_offset_scale(scale);
    this->_notify_update();
}

void Transform2DComponent::set_local_scale(float scale) {
    this->_transform_system->set_offset_scale(Vector2Scale(this->_transform_system->get_origin_scale(), scale));
    this->_notify_update();
}

void Transform2DComponent::set_world_position(Vector2 position) {
    this->_transform_system->set_result_position(position);
    this->_notify_update();
}

void Transform2DComponent::set_world_rotation(float rotation) {
    this->_transform_system->set_result_rotation(rotation);
    this->_notify_update();
}

void Transform2DComponent::set_world_scale(Vector2 scale) {
    this->_transform_system->set_result_scale(scale);
    this->_notify_update();
}

void Transform2DComponent::set_world_scale(float scale) {
    this->_transform_system->set_result_scale(Vector2Scale(this->_transform_system->get_origin_scale(), scale));
    this->_notify_update();
}

void Transform2DComponent::translate(Vector2 translation) {
    this->_transform_system->set_offset_position(Vector2Add(this->_transform_system->get_offset_position(), translation));
    this->_notify_update();
}

void Transform2DComponent::rotate(float rotation) {
    this->_transform_system->set_offset_rotation(this->_transform_system->get_offset_rotation() + rotation);
    this->_notify_update();
}

void Transform2DComponent::scale(Vector2 scale) {
    this->_transform_system->set_offset_scale(Vector2Multiply(this->_transform_system->get_offset_scale(), scale));
    this->_notify_update();
}

void Transform2DComponent::scale(float scale) {
    this->_transform_system->set_offset_scale(Vector2Scale(this->_transform_system->get_offset_scale(), scale));
    this->_notify_update();
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
    this->_transform_system->set_origin(parent_transform->get_world_transform());
    this->_notify_update();
}
