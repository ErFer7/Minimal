#pragma once

#include <string>

#include "../entities/entity.h"
#include "../utils/dynamic_array.h"
#include "../utils/engine_core_dependent_injector.h"

class EngineCore;

class Entity;

class EntityContainer : public EngineCoreDependentInjector {
   public:
    EntityContainer(EngineCore *engine_core);
    ~EntityContainer();

    void add_entity(Entity *entity);
    void remove_all_entities();
    Entity *find_entity(unsigned int entity_id);
    Entity *find_entity(std::string entity_name);
    bool remove_entity(unsigned int entity_id);
    bool remove_entity(std::string entity_name);

   private:
    Entity *_root;
};