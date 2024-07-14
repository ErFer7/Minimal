#pragma once

#include <string>

#include "../utils/engine_core_dependency_injector.h"

class EngineCore;
class Entity;

class Component : public EngineCoreDependencyInjector {
   public:
    Component(EngineCore *engine_core, bool unique);
    virtual ~Component() = default;

    inline bool is_active() const { return this->_active; }
    inline void set_active(bool active) { this->_active = active; }
    inline bool is_unique() const { return this->_unique; }
    inline Entity *get_entity() { return this->_entity; }
    inline void set_entity(Entity *entity) { this->_entity = entity; }
    virtual void on_add_to_entity() = 0;
    virtual void on_remove_from_entity() = 0;
    virtual void on_entity_parent_added(Entity *parent) = 0;
    virtual void on_entity_parent_removed(Entity *parent) = 0;

   private:
    bool _active;
    bool _unique;
    Entity *_entity;
};
