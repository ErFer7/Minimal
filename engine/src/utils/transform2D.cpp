#include "../../include/utils/transform2D.h"

Transform2D::Transform2D() {
    this->_position = Vector2Zero();
    this->_rotation = 0.0f;
    this->_scale = Vector2One();
}
