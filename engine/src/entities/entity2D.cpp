#include "../../include/entities/entity2D.h"

Entity2D::Entity2D(std::string name, bool auto_managed) : Entity(name, auto_managed) {
    this->add_component(new Transform2DComponent());
    this->add_component(new Graphics2DComponent());
}