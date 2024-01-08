#pragma once

#include <functional>
#include <string>
#include <typeinfo>

#include "dynamic_array.h"
#include "entity.h"
#include "manager.h"

class Entity;

class EntityManager : public Manager {
   public:
    EntityManager(EngineCore *engine_core);
    ~EntityManager() override;
    inline DynamicArrayIterator<Entity *> *get_entities_iterator() {
        return new DynamicArrayIterator<Entity *>(this->_entities);
    }
    inline unsigned int get_entity_count() const { return this->_entities->get_element_count(); }
    inline unsigned int get_temp_component_count() const { return this->_temp_components->get_element_count(); }
    void add_entity(Entity *entity);
    void remove_all_entities();
    Entity *find_entity(unsigned int entity_id);
    Entity *find_entity(std::string entity_name);
    bool remove_entity(unsigned int entity_id);
    bool remove_entity(std::string entity_name);
    void init() override {}
    void update() override;
    void exit() override {}

    template <typename T>
    Component *get_temp_component() {
        for (unsigned int i = 0; i < this->_temp_components->get_size(); i++) {
            Component *component = this->_temp_components->nullable_at(i);
            if (component != nullptr && typeid(*component) == typeid(T)) {
                return this->_temp_components->nullable_pop_at(i, false);
            }
        }

        return nullptr;
    }

   private:
    Entity *_root;
    DynamicArray<Entity *> *_entities;
    DynamicArray<Component *> *_temp_components;

    void _unregister_entity(Entity *entity);
    void _on_temp_component_remove(Component *component);
    void _register_entity(Entity *entity);

    friend class Entity;
};