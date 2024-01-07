#include "../include/behaviour_manager.h"

BehaviourManager::BehaviourManager(EngineCore *engine_core) {
    this->_engine_core = engine_core;
    this->_behaviour_components = new DynamicArray<BehaviourComponent *>(256, 32);
}

BehaviourManager::~BehaviourManager() {}

void BehaviourManager::update_component_references() {
    EntityManager *entity_manager = this->_engine_core->get_entity_manager();

    if (entity_manager->get_temp_component_count() > 0) {
        while (true) {
            BehaviourComponent *behaviour_component =
                static_cast<BehaviourComponent *>(entity_manager->get_temp_component<BehaviourComponent>());

            if (behaviour_component == nullptr) {
                break;
            }

            this->_behaviour_components->add(behaviour_component);
            behaviour_component->on_init();
        }
    }

    this->_behaviour_components->optimize();
}

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

void BehaviourManager::_on_component_remove(Component *component) {
    BehaviourComponent *behaviour_component = static_cast<BehaviourComponent *>(component);

    if (behaviour_component->is_active()) {
        behaviour_component->on_exit();
    }

    this->_behaviour_components->remove(behaviour_component, false);
}
