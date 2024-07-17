#pragma once

#include "../../engine/include/minimal.hpp"

class CustomMainBehaviourManager final : public MainBehaviourManager {
   public:
    CustomMainBehaviourManager(EngineCore *engine_core) : MainBehaviourManager(engine_core){};
    ~CustomMainBehaviourManager() final = default;
    void init() final;
    void update() final;
    void exit() final;

   private:
    Entity2D *_player;
    Entity2D *_ground;
};