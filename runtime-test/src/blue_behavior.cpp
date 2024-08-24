#include "../include/blue_behavior.hpp"

#include <math.h>
#include <cstdlib>

#include "components/transform2D_component.hpp"
#include "entities/entity2D.hpp"

void BlueBehavior::update() {
    Transform2DComponent *transform = static_cast<Entity2D *>(this->get_entity())->get_transform_component();
    transform->set_scale(Vector2{static_cast<float>(abs(cos(GetTime()))), static_cast<float>(abs(sin(GetTime())))});
}
