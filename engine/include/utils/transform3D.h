#pragma once

#include "raylib.h"
#include "raymath.h"

class Transform3D {
   public:
    Transform3D();
    Transform3D(Vector3 position, Quaternion rotation, Vector3 scale)
        : _position(position), _rotation(rotation), _scale(scale) {}
    ~Transform3D() = default;

    inline Vector3 get_position() { return this->_position; }
    inline void set_position(Vector3 position) { this->_position = position; }
    inline Quaternion get_rotation() { return this->_rotation; }
    inline void set_rotation(Quaternion rotation) { this->_rotation = rotation; }
    inline Vector3 get_scale() { return this->_scale; }
    inline void set_scale(Vector3 scale) { this->_scale = scale; }

   private:
    Vector3 _position;
    Quaternion _rotation;
    Vector3 _scale;
};
