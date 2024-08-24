#include "../include/green_behavior.hpp"

#include <math.h>

#include "components/transform2D_component.hpp"
#include "entities/entity2D.hpp"

void GreenBehavior::update() {
    Transform2DComponent *transform = static_cast<Entity2D *>(this->get_entity())->get_transform_component();
    transform->rotate(1.0f);
}
