#pragma once

#include "behaviour_manager.h"
#include "component.h"

class BehaviourComponent : public Component {
   public:
    BehaviourComponent(bool unique, std::string name = "") : Component(unique, name) {}
    ~BehaviourComponent() override = default;

   protected:
    void register_component() override;
    void unregister_component() override;
};