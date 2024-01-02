#pragma once

#include <string>
#include <unordered_map>

#include "entity.h"
#include "entity_group.h"

class EntityContainer {
    typedef std::unordered_map<std::string, EntityGroup *> EntityGroups;

   public:
    EntityContainer();
    ~EntityContainer();
    void create_entity_group(const std::string &group_name);
    void add_entity_to_group(const std::string &group_name, Entity *entity);
    void remove_entity_from_group(const std::string &group_name, Entity *entity);
    void clear_entity_group(const std::string &group_name);
    void delete_entity_group(const std::string &group_name);

   private:
    EntityGroups *_entity_groups;
};