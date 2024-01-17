#include "../../include/utils/transform_system2D.h"

TransformSystem2D::TransformSystem2D() {
    this->_origin = Transform2D();
    this->_offset = Transform2D();
    this->_result = Transform2D();
}

void TransformSystem2D::set_origin(Transform2D origin) {
    this->_origin = origin;
    this->_update_result();
}

void TransformSystem2D::set_offset(Transform2D offset) {
    this->_offset = offset;
    this->_update_result();
}

void TransformSystem2D::set_result(Transform2D result) {
    this->_result = result;
    this->_update_offset();
}

void TransformSystem2D::set_origin_position(Vector2 position) {
    this->_origin.set_position(position);
    this->_update_result();
}

void TransformSystem2D::set_origin_rotation(float rotation) {
    this->_origin.set_rotation(rotation);
    this->_update_result();
}

void TransformSystem2D::set_origin_scale(Vector2 scale) {
    this->_origin.set_scale(scale);
    this->_update_result();
}

void TransformSystem2D::set_offset_position(Vector2 position) {
    this->_offset.set_position(position);
    this->_update_result();
}

void TransformSystem2D::set_offset_rotation(float rotation) {
    this->_offset.set_rotation(rotation);
    this->_update_result();
}

void TransformSystem2D::set_offset_scale(Vector2 scale) {
    this->_offset.set_scale(scale);
    this->_update_result();
}

void TransformSystem2D::set_result_position(Vector2 position) {
    this->_result.set_position(position);
    this->_update_offset();
}

void TransformSystem2D::set_result_rotation(float rotation) {
    this->_result.set_rotation(rotation);
    this->_update_offset();
}

void TransformSystem2D::set_result_scale(Vector2 scale) {
    this->_result.set_scale(scale);
    this->_update_offset();
}

void TransformSystem2D::_update_result() {
    this->_result.set_position(Vector2Add(this->_origin.get_position(), this->_offset.get_position()));
    this->_result.set_rotation(this->_origin.get_rotation() + this->_offset.get_rotation());
    this->_result.set_scale(Vector2Multiply(this->_origin.get_scale(), this->_offset.get_scale()));
}

void TransformSystem2D::_update_offset() {
    Vector2 position_difference = Vector2Subtract(this->_result.get_position(), this->_origin.get_position());
    float rotation_difference = this->_result.get_rotation() - this->_origin.get_rotation();
    Vector2 scale_difference = Vector2Divide(this->_result.get_scale(), this->_origin.get_scale());

    this->_offset.set_position(Vector2Add(this->_offset.get_position(), position_difference));
    this->_offset.set_rotation(this->_offset.get_rotation() + rotation_difference);
    this->_offset.set_scale(Vector2Multiply(this->_offset.get_scale(), scale_difference));
}
