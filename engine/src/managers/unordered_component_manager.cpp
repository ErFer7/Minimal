#include "../../include/managers/unordered_component_manager.hpp"

#include <algorithm>
#include <memory>

UnorderedComponentManager::UnorderedComponentManager(EngineCore *engine_core) : ComponentManager(engine_core) {
    this->_components = std::make_unique<std::vector<Component *>>();
}

void UnorderedComponentManager::unregister_component(Component *component) {
    auto it = std::remove(this->_components->begin(), this->_components->end(), component);
    this->_components->erase(it, this->_components->end());
}
