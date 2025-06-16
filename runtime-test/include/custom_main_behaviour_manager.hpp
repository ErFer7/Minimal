#pragma once

#include "../../engine/include/minimal.hpp"
#include "entities/entity2D.hpp"

class CustomMainBehaviourManager final : public MainBehaviourManager {
   public:
    CustomMainBehaviourManager(EngineCore *engine_core) : MainBehaviourManager(engine_core){};

    ~CustomMainBehaviourManager() final = default;

    void init() final;

    void update() final;

    void exit() final;

   private:
    Entity2D *_entity_r;
    Entity2D *_entity_g;
    Entity2D *_entity_b;
    Entity2D *_child;
};