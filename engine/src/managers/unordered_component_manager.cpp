#include "../../include/managers/unordered_component_manager.h"

UnorderedComponentManager::UnorderedComponentManager(EngineCore *engine_core) : ComponentManager(engine_core) {
    this->_components = new DynamicArray<Component *>(32);
}

UnorderedComponentManager::~UnorderedComponentManager() {
    if (this->_components != nullptr) {
        delete this->_components;
        this->_components = nullptr;
    }
}
