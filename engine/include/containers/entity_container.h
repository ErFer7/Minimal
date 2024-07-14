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

    void create_entity();
    void destroy_entity();

    void destroy_all_entities();

   private:
    std::unique_ptr<Entity> _root;
};