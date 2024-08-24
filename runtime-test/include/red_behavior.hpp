#pragma once

#include "../../engine/include/minimal.hpp"

class RedBehavior final : public BehaviourComponent {
   public:
    RedBehavior(EngineCore *engine_core, Entity *entity) : BehaviourComponent(engine_core, entity, false){};
    ~RedBehavior() final = default;

    void start() final {}
    void update() final;

   private:
};
