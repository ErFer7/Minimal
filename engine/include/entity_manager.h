#pragma once

#include <string>

#include "dynamic_array.h"
#include "entity.h"
#include "manager_interface.h"

class EntityManager : public IManager {
   public:
    EntityManager();
    ~EntityManager() override;
    inline void add_entity(Entity *entity) { this->_root->add_child(entity); }
    inline void remove_all_entities() { this->_root->remove_all_children(); }
    Entity *find_entity(unsigned int entity_id);
    Entity *find_entity(std::string entity_name);
    bool remove_entity(Entity *entity);
    bool remove_entity(unsigned int entity_id);
    bool remove_entity(std::string entity_name);
    void init() override {}
    void update() override;
    void exit() override {}

   private:
    Entity *_root;
    DynamicArray<Entity *> *_entities;
};