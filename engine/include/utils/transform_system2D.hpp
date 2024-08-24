#pragma once

#include <raylib.h>

#include "transform.hpp"

class TransformSystem2D {
   public:
    TransformSystem2D(){};

    ~TransformSystem2D() = default;

    inline const Transform2D get_absolute() const { return this->_absolute; }

    inline const Vector2 get_absolute_position() const { return this->_absolute.position; }

    inline float get_absolute_rotation() const { return this->_absolute.rotation; }

    inline const Vector2 get_absolute_scale() const { return this->_absolute.scale; }

    const Transform2D get_relative(Transform2D origin) const;

    inline const Vector2 get_relative_position(Vector2 origin_position) const {
        return Vector2Subtract(this->_absolute.position, origin_position);
    }

    inline float get_relative_rotation(float origin_rotation) const { return this->_absolute.rotation - origin_rotation; }

    inline const Vector2 get_relative_scale(Vector2 origin_scale) const { return Vector2Divide(this->_absolute.scale, origin_scale); }

    inline void set_absolute(Transform2D result) { this->_absolute = result; }

    void set_relative(Transform2D origin, Transform2D offset);

    inline void set_absolute_position(Vector2 position) { this->_absolute.position = position; }

    inline void set_absolute_rotation(float rotation) { this->_absolute.rotation = rotation; }

    inline void set_absolute_scale(Vector2 scale) { this->_absolute.scale = scale; }

    inline void set_relative_position(Vector2 origin_position, Vector2 offset_position) {
        this->_absolute.position = Vector2Subtract(offset_position, origin_position);
    }

    inline void set_relative_rotation(float origin_rotation, float offset_rotation) {
        this->_absolute.rotation = offset_rotation - origin_rotation;
    }

    inline void set_relative_scale(Vector2 origin_scale, Vector2 offset_scale) {
        this->_absolute.scale = Vector2Divide(offset_scale, origin_scale);
    }

    inline void translate(Vector2 translation) { this->_absolute.position = Vector2Add(this->_absolute.position, translation); }

    inline void rotate(float rotation) { this->_absolute.rotation = this->_absolute.rotation + rotation; }

    inline void scale(Vector2 scale) { this->_absolute.scale = Vector2Multiply(this->_absolute.scale, scale); }

   private:
    Transform2D _absolute;
};