#pragma once

#include <typeinfo>

#include "behaviour_component.h"
#include "engine_core.h"
#include "entity.h"
#include "entity_manager.h"
#include "manager_interface.h"

class EngineCore;

class BehaviourManager : public IManager {
   public:
    BehaviourManager(EngineCore *engine_core);
    ~BehaviourManager();
    void update_component_references();
    void init() override;
    void update() override;
    void exit() override;

   private:
    EngineCore *_engine_core;
    DynamicArray<BehaviourComponent *> *_behaviour_components;

    void _on_component_remove(Component *component);
};
