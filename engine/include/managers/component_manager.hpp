#pragma once

#include <memory>
#include <vector>

#include "../components/component.hpp"
#include "../types.hpp"
#include "manager.hpp"

class ComponentManager : public Manager {
   public:
    ComponentManager() = default;
    ComponentManager(EngineCore *engine_core) : Manager(engine_core){};
    ~ComponentManager() override = default;

    void update() override {};

   protected:
    inline Component *register_component(Component component) {
        this->_components->push_back(component);
        return &this->_components->back();
    }

    void unregister_component(Component *component);

   private:
    std::unique_ptr<std::vector<Component>> _components;
};
