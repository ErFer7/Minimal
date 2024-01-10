#include "../../include/managers/physics_manager.h"

void PhysicsManager::init() {}

void PhysicsManager::update() {
    DynamicArray<Component *> *components = this->get_components();

    for (unsigned int i = 0; i < components->get_size(); i++) {
        PhysicsComponent *physics_component = static_cast<PhysicsComponent *>(components->nullable_at(i));

        if (physics_component != nullptr && physics_component->is_active()) {
            // TODO: Implement physics
        }
    }

    this->ComponentManager::update();
}

void PhysicsManager::exit() {}
