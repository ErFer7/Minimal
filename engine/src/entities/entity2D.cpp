#include "../../include/entities/entity2D.h"

Entity2D::Entity2D(EngineCore *engine_core, std::string name, bool auto_managed)
    : Entity(engine_core, name, auto_managed) {
    this->_transform_component = this->create<Transform2DComponent>();
    this->_graphics_component = this->create<Graphics2DComponent>();

    this->create_component(this->_transform_component);
    this->create_component(this->_graphics_component);
}