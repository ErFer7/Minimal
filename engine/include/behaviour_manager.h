#pragma once

#include <typeinfo>

#include "behaviour_component.h"
#include "component_manager.h"
#include "engine_core.h"

class BehaviourComponent;

class BehaviourManager : public ComponentManager {
   public:
    BehaviourManager(EngineCore *engine_core) : ComponentManager(engine_core){};
    ~BehaviourManager() override = default;
    void init() override;
    void update() override;
    void exit() override;

   private:
    friend class BehaviourComponent;
};
