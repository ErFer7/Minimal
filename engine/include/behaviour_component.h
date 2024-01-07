#pragma once

#include "component.h"

class BehaviourComponent : public Component {
   public:
    BehaviourComponent(bool unique, std::string name = "") : Component(unique, name) {}
    ~BehaviourComponent() override = default;
    virtual void on_init() {};
    virtual void on_update() override {};
    virtual void on_exit() {};
};