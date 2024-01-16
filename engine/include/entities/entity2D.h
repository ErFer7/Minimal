#pragma once

#include "../components/graphics2D_component.h"
#include "../components/transform2D_component.h"
#include "entity.h"

class Entity2D : public Entity {
   public:
    Entity2D(EngineCore *engine_core, std::string name = "", bool auto_managed = true);
    ~Entity2D() = default;

    inline Transform2DComponent *get_transform_component() {
        return this->_transform_component;
    }
    inline Graphics2DComponent *get_graphics_component() {
        return this->_graphics_component;
    }

   private:
    Transform2DComponent *_transform_component;
    Graphics2DComponent *_graphics_component;
};