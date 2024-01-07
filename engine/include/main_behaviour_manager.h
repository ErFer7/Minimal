#pragma once

#include "engine_core.h"
#include "manager_interface.h"

class EngineCore;

class MainBehaviourManager : public IManager {
   public:
    MainBehaviourManager(EngineCore *engine_core);
    ~MainBehaviourManager() override{};
    inline EngineCore *get_engine_core() { return this->_engine_core; };
    void init() override{};
    void update() override{};
    void exit() override{};

   private:
    EngineCore *_engine_core;
};