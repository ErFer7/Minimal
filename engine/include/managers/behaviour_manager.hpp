#pragma once

#include "../types.hpp"
#include "unordered_component_manager.hpp"

class BehaviourManager : public UnorderedComponentManager {
    friend class BehaviourComponent;

   public:
    BehaviourManager() = default;
    BehaviourManager(EngineCore *engine_core) : UnorderedComponentManager(engine_core){};
    ~BehaviourManager() override = default;

    void init() override;
    void update() override;
    void exit() override;
};
