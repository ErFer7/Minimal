#include "../../include/managers/behaviour_manager.hpp"

#include <vector>

#include "../../include/components/behaviour_component.hpp"

void BehaviourManager::init() {}

void BehaviourManager::update() {
    std::vector<Component *> *components = this->get_components();

    for (unsigned int i = 0; i < components->size(); i++) {
        BehaviourComponent *behaviour_component = static_cast<BehaviourComponent *>(components->at(i));

        behaviour_component->update();
    }

    this->ComponentManager::update();
}

void BehaviourManager::exit() {}
