#pragma once

#include "../utils/dynamic_array.h"
#include "component_manager.h"

class Component;

class UnorderedComponentManager : public ComponentManager {
   public:
    UnorderedComponentManager() = default;
    UnorderedComponentManager(EngineCore *engine_core);
    ~UnorderedComponentManager() override;

    inline void update() override { this->_components->optimize(); };

   protected:
    inline void register_component(Component *component) override { this->_components->add(component); }
    inline void unregister_component(Component *component) override { this->_components->remove(component, false); }
    inline DynamicArray<Component *> *get_components() { return this->_components; }

   private:
    DynamicArray<Component *> *_components;
};
