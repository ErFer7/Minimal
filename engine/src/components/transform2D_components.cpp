#include "../../include/components/transform2D_component.h"

Transform2DComponent::Transform2DComponent(std::string name) : Component(true, name) {
    this->_position = Vector2Zero();
    this->_rotation = 0.0f;
    this->_scale = Vector2One();
}