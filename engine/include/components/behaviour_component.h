#pragma once

#include "../managers/behaviour_manager.h"
#include "managed_component.h"

class BehaviourComponent : public ManagedComponent {
   public:
    BehaviourComponent(bool unique, std::string name = "") : ManagedComponent(unique, name) {}
    ~BehaviourComponent() override = default;

    virtual void update() = 0;

   protected:
    void register_component() override;
    void unregister_component() override;
};