#pragma once

#include "component.h"

class ManagedComponent : public Component {
   public:
    ManagedComponent(EngineCore *engine_core, bool unique, std::string name = "") : Component(engine_core, unique, name) {}
    ~ManagedComponent() override = default;

   protected:
    virtual void register_component() = 0;
    virtual void unregister_component() = 0;

    friend class Entity;
};