#include "../../include/managers/behaviour_manager.h"

void BehaviourManager::init() {
    DynamicArray<Component *> *components = this->get_components();

    for (unsigned int i = 0; i < components->get_size(); i++) {
        BehaviourComponent *behaviour_component = static_cast<BehaviourComponent *>(components->nullable_at(i));

        if (behaviour_component != nullptr && behaviour_component->is_active()) {
            behaviour_component->on_init();
        }
    }
}

void BehaviourManager::update() {
    DynamicArray<Component *> *components = this->get_components();

    for (unsigned int i = 0; i < components->get_size(); i++) {
        BehaviourComponent *behaviour_component = static_cast<BehaviourComponent *>(components->nullable_at(i));

        if (behaviour_component != nullptr && behaviour_component->is_active()) {
            behaviour_component->on_update();
        }
    }

    this->ComponentManager::update();
}

void BehaviourManager::exit() {
    DynamicArray<Component *> *components = this->get_components();

    for (unsigned int i = 0; i < components->get_size(); i++) {
        BehaviourComponent *behaviour_component = static_cast<BehaviourComponent *>(components->nullable_at(i));

        if (behaviour_component != nullptr && behaviour_component->is_active()) {
            behaviour_component->on_exit();
        }
    }
}
