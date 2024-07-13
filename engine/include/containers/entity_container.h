#pragma once

#include <memory>
#include <string>

#include "../entities/entity.h"
#include "../utils/dynamic_array.hpp"
#include "../utils/engine_core_dependency_injector.h"

class EngineCore;

class Entity;

class EntityContainer : public EngineCoreDependencyInjector {
   public:
    EntityContainer() = default;
    EntityContainer(EngineCore *engine_core);
    ~EntityContainer();

    void add_entity(Entity *entity);
    void remove_all_entities();

   private:
    Entity _root;
};