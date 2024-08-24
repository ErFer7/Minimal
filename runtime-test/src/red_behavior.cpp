#include "../include/red_behavior.hpp"

#include <math.h>

#include "components/transform2D_component.hpp"
#include "entities/entity2D.hpp"

void RedBehavior::update() {
    Transform2DComponent *transform = static_cast<Entity2D *>(this->get_entity())->get_transform_component();
    transform->translate(Vector2{static_cast<float>(cos(GetTime())), static_cast<float>(sin(GetTime()))});
}
