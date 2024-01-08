#pragma once

#include <typeinfo>

#include "behaviour_component.h"
#include "dynamic_array.h"
#include "manager.h"

class BehaviourManager : public Manager {
   public:
    BehaviourManager(EngineCore *engine_core);
    ~BehaviourManager();
    void init() override;
    void update() override;
    void exit() override;

   private:
    DynamicArray<BehaviourComponent *> *_behaviour_components;

    void _register_component(BehaviourComponent *behaviour_component);
    void _unregister_component(BehaviourComponent *behaviour_component);

    friend class BehaviourComponent;
};
