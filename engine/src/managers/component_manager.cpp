#include "../../include/managers/component_manager.h"

ComponentManager::ComponentManager(EngineCore *engine_core) : Manager(engine_core) {
    this->_components = new DynamicArray<Component *>(256, 32);
}

ComponentManager::~ComponentManager() {
    if (this->_components != nullptr) {
        delete this->_components;
        this->_components = nullptr;
    }
}
