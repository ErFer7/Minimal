#pragma once

#include "../types.hpp"
#include "unordered_component_manager.hpp"

class PhysicsComponent;

class PhysicsManager : public UnorderedComponentManager {
   public:
    PhysicsManager() = default;
    PhysicsManager(EngineCore *engine_core) : UnorderedComponentManager(engine_core){};
    ~PhysicsManager() override = default;

    void init() override;
    void update() override;
    void exit() override;

   private:
    friend class PhysicsComponent;
};
