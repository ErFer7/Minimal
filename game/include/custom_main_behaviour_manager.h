#pragma once

#include "../../engine/include/minimal.h"

class CustomMainBehaviourManager : public MainBehaviourManager {
   public:
    CustomMainBehaviourManager(EngineCore *engine_core) : MainBehaviourManager(engine_core){};
    ~CustomMainBehaviourManager() final = default;
    void init() final;
    void update() final;
    void exit() final;
};