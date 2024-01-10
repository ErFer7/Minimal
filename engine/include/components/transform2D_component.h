#pragma once

#include "component.h"
#include "raymath.h"

class Transform2DComponent : public Component {
   public:
    Transform2DComponent(std::string name = "");
    ~Transform2DComponent() override = default;
    inline Vector2 get_position() const { return this->_position; }
    inline void set_position(Vector2 position) { this->_position = position; }
    inline float get_rotation() const { return this->_rotation; }
    inline void set_rotation(float rotation) { this->_rotation = rotation; }
    inline Vector2 get_scale() const { return this->_scale; }
    inline void set_scale(Vector2 scale) { this->_scale = scale; }
    inline void translate(Vector2 translation) { this->_position = Vector2Add(this->_position, translation); }
    inline void rotate(float rotation) { this->_rotation += rotation; }
    inline void scale(Vector2 scale) { this->_scale = Vector2Multiply(this->_scale, scale); }

   private:
    Vector2 _position;
    float _rotation;
    Vector2 _scale;
};