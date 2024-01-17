#include "../../include/utils/transform3D.h"

Transform3D::Transform3D() {
    this->_position = Vector3Zero();
    this->_rotation = QuaternionIdentity();
    this->_scale = Vector3One();
}