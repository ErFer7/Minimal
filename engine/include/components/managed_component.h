#pragma once

#include "component.h"

class ManagedComponent : public Component {
   public:
    ManagedComponent(bool unique, std::string name = "") : Component(unique, name) {}
    ~ManagedComponent() override = default;

   protected:
    virtual void register_component() = 0;
    virtual void unregister_component() = 0;

    friend class Entity;
};