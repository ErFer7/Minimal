#pragma once

#include "raylib.h"
#include "raymath.h"

class Transform2D {
   public:
    Transform2D();
    ~Transform2D() = default;

    inline Vector2 get_position() { return this->_position; }
    inline void set_position(Vector2 position) { this->_position = position; }
    inline float get_rotation() { return this->_rotation; }
    inline void set_rotation(float rotation) { this->_rotation = rotation; }
    inline Vector2 get_scale() { return this->_scale; }
    inline void set_scale(Vector2 scale) { this->_scale = scale; }

   private:
    Vector2 _position;
    float _rotation;
    Vector2 _scale;
};
