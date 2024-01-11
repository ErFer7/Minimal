#pragma once

#include "../utils/dynamic_array.h"
#include "manager.h"

class Component;

class ComponentManager : public Manager {
   public:
    ComponentManager(EngineCore *engine_core);
    ~ComponentManager() override;

    inline void update() override { this->_components->optimize(); };

   protected:
    inline void register_component(Component *component) { this->_components->add(component); }
    inline void unregister_component(Component *component) { this->_components->remove(component, false); }
    inline DynamicArray<Component *> *get_components() { return this->_components; }

   private:
    DynamicArray<Component *> *_components;
};
