#pragma once

#include "../../engine/include/minimal.hpp"

class BlueBehavior final : public BehaviourComponent {
   public:
    BlueBehavior(EngineCore *engine_core, Entity *entity) : BehaviourComponent(engine_core, entity, false){};

    ~BlueBehavior() final = default;

    void start() final {}

    void update() final;

   private:
};
