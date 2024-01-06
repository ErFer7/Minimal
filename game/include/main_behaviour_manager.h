#pragma once

#include "../../engine/include/engine_core.h"
#include "../../engine/include/manager_interface.h"

class MainBehaviourManager : public IManager {
   public:
    MainBehaviourManager(EngineCore *engine_core);
    ~MainBehaviourManager() final;
    void init() final;
    void update() final;
    void exit() final;

   private:
    EngineCore *_engine_core;
};