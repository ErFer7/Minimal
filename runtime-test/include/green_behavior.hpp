#pragma once

#include "../../engine/include/minimal.hpp"

class GreenBehavior final : public BehaviourComponent {
   public:
    GreenBehavior(EngineCore *engine_core, Entity *entity) : BehaviourComponent(engine_core, entity, false){};

    ~GreenBehavior() final = default;

    void start() final {}

    void update() final;

   private:
};
