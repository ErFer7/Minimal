#pragma once

#include "transform.hpp"

class TransformSystem2D {
   public:
    TransformSystem2D();
    ~TransformSystem2D() = default;

    inline const Transform2D get_origin() const { return this->_origin; }
    inline const Transform2D get_offset() const { return this->_offset; }
    inline const Transform2D get_result() const { return this->_result; }
    inline const Vector2 get_origin_position() const { return this->_origin.get_position(); }
    inline const float get_origin_rotation() const { return this->_origin.get_rotation(); }
    inline const Vector2 get_origin_scale() const { return this->_origin.get_scale(); }
    inline const Vector2 get_offset_position() const { return this->_offset.get_position(); }
    inline const float get_offset_rotation() const { return this->_offset.get_rotation(); }
    inline const Vector2 get_offset_scale() const { return this->_offset.get_scale(); }
    inline const Vector2 get_result_position() const { return this->_result.get_position(); }
    inline const float get_result_rotation() const { return this->_result.get_rotation(); }
    inline const Vector2 get_result_scale() const { return this->_result.get_scale(); }
    void set_origin(Transform2D origin);
    void set_offset(Transform2D offset);
    void set_result(Transform2D result);
    void set_origin_position(Vector2 position);
    void set_origin_rotation(float rotation);
    void set_origin_scale(Vector2 scale);
    void set_offset_position(Vector2 position);
    void set_offset_rotation(float rotation);
    void set_offset_scale(Vector2 scale);
    void set_result_position(Vector2 position);
    void set_result_rotation(float rotation);
    void set_result_scale(Vector2 scale);

   private:
    Transform2D _origin;
    Transform2D _offset;
    Transform2D _result;

    void _update_result();
    void _update_offset();
};