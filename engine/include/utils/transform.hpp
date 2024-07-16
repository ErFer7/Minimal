#pragma once

#include <typeinfo>

#include "raylib.h"
#include "raymath.h"

template <typename VectorT>
class TransformT {
   public:
    TransformT() {
        if (typeid(VectorT) == typeid(Vector2)) {
            this->_position = Vector2Zero();
            this->_rotation = 0.0f;
            this->_scale = Vector2One();
        } else if (typeid(VectorT) == typeid(Vector3)) {
            this->_position = Vector3Zero();
            this->_rotation = QuaternionIdentity();
            this->_scale = Vector3One();
        }
    }
    ~TransformT() = default;

    inline const VectorT get_position() const { return this->_position; }
    inline void set_position(VectorT position) { this->_position = position; }
    inline const float get_rotation() const { return this->_rotation; }
    inline void set_rotation(float rotation) { this->_rotation = rotation; }
    inline const VectorT get_scale() const { return this->_scale; }
    inline void set_scale(VectorT scale) { this->_scale = scale; }

   private:
    VectorT _position;
    float _rotation;
    VectorT _scale;
};

typedef TransformT<Vector2> Transform2D;
typedef TransformT<Vector3> Transform3D;
