#pragma once

#include "../types.hpp"
#include "component.hpp"

class ManagedComponent : public Component {
   public:
    ManagedComponent(EngineCore *engine_core, Entity *entity, bool unique) : Component(engine_core, entity, unique) {}
    ~ManagedComponent() override = default;

   protected:
    virtual void register_component() = 0;
    virtual void unregister_component() = 0;

    friend class Entity;
};