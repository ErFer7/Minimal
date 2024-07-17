#pragma once

#include <memory>
#include <vector>

#include "../types.hpp"
#include "component_manager.hpp"

class UnorderedComponentManager : public ComponentManager {
   public:
    UnorderedComponentManager() = default;
    UnorderedComponentManager(EngineCore *engine_core);
    ~UnorderedComponentManager() override = default;

    inline void update() override {};

   protected:
    inline void register_component(Component *component) override { this->_components->push_back(component); }
    void unregister_component(Component *component) override;
    inline std::vector<Component *> *get_components() { return this->_components.get(); }

   private:
    std::unique_ptr<std::vector<Component *>> _components;
};
