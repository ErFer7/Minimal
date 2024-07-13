#pragma once

#include <typeinfo>

#include "../components/behaviour_component.h"
#include "../engine_core.hpp"
#include "unordered_component_manager.h"

class BehaviourComponent;

class BehaviourManager : public UnorderedComponentManager {
   public:
    BehaviourManager() = default;
    BehaviourManager(EngineCore *engine_core) : UnorderedComponentManager(engine_core){};
    ~BehaviourManager() override = default;

    void init() override;
    void update() override;
    void exit() override;

   private:
    friend class BehaviourComponent;
};
