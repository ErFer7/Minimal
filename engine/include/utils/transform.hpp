#pragma once

#include "raymath.h"

struct Transform2D {
    Transform2D() : position(Vector2Zero()), rotation(0), scale(Vector2One()) {}

    Vector2 position;
    float rotation;
    Vector2 scale;
};

struct Transform3D {
    Transform3D() : position(Vector3Zero()), rotation(Vector3Zero()), scale(Vector3One()) {}

    Vector3 position;
    Vector3 rotation;
    Vector3 scale;
};
