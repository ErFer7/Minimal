#pragma once

#include "../components/graphics2D_component.h"
#include "../components/transform2D_component.h"
#include "entity.h"

class Entity2D : public Entity {
   public:
    Entity2D(std::string name = "", bool auto_managed = true);
    ~Entity2D() = default;

    inline Transform2DComponent *get_transform_component() {
        return static_cast<Transform2DComponent *>(this->get_component<Transform2DComponent>());
    }
    inline Graphics2DComponent *get_graphics_component() {
        return static_cast<Graphics2DComponent *>(this->get_component<Graphics2DComponent>());
    }
};