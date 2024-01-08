#include "../include/behaviour_manager.h"

BehaviourManager::BehaviourManager(EngineCore *engine_core) : Manager(engine_core) {
    this->_behaviour_components = new DynamicArray<BehaviourComponent *>(256, 32);
}

BehaviourManager::~BehaviourManager() { delete this->_behaviour_components; }

void BehaviourManager::init() {
    for (unsigned int i = 0; i < this->_behaviour_components->get_size(); i++) {
        BehaviourComponent *behaviour_component = this->_behaviour_components->nullable_at(i);

        if (behaviour_component != nullptr && behaviour_component->is_active()) {
            behaviour_component->on_init();
        }
    }
}

void BehaviourManager::update() {
    for (unsigned int i = 0; i < this->_behaviour_components->get_size(); i++) {
        BehaviourComponent *behaviour_component = this->_behaviour_components->nullable_at(i);

        if (behaviour_component != nullptr && behaviour_component->is_active()) {
            behaviour_component->on_update();
        }
    }
}

void BehaviourManager::exit() {
    for (unsigned int i = 0; i < this->_behaviour_components->get_size(); i++) {
        BehaviourComponent *behaviour_component = this->_behaviour_components->nullable_at(i);

        if (behaviour_component != nullptr && behaviour_component->is_active()) {
            behaviour_component->on_exit();
        }
    }
}

void BehaviourManager::_register_component(BehaviourComponent *behaviour_component) {
    this->_behaviour_components->add(behaviour_component);
}

void BehaviourManager::_unregister_component(BehaviourComponent *behaviour_component) {
    this->_behaviour_components->remove(behaviour_component, false);
}
