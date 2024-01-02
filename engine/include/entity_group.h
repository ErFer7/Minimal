#pragma once

#include <unordered_map>

#include "entity.h"

class EntityGroup {
    typedef std::unordered_map<unsigned int, Entity *> Entities;

   public:
    EntityGroup();
    ~EntityGroup();
    void add_entity(Entity *entity);
    void remove_entity(Entity *entity);
    void clear_entities();

   private:
    Entities *_entities;
};