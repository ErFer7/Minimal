#pragma once

#include "manager.hpp"

class MainBehaviourManager : public Manager {
   public:
    MainBehaviourManager() = default;
    MainBehaviourManager(EngineCore *engine_core) : Manager(engine_core){};
    ~MainBehaviourManager() override {}

    void init() override {};
    void update() override {};
    void exit() override {};
};