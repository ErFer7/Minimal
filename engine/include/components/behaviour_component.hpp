#pragma once

#include "../types.hpp"
#include "managed_component.hpp"

class BehaviourComponent : public ManagedComponent {
   public:
    BehaviourComponent(EngineCore *engine_core, Entity *entity, bool unique) : ManagedComponent(engine_core, entity, unique) {}
    ~BehaviourComponent() override;

    virtual void update() = 0;

   protected:
    void register_component() override;
    void unregister_component() override;
};