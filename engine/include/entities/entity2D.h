#pragma once

#include "entity.h"
#include "../components/transform2D_component.h"

class Entity2D : public Entity {
   public:
    Entity2D(std::string name = "", bool auto_managed = true);
    ~Entity2D() = default;
};