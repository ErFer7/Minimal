#pragma once

#include <string>

#include "../utils/engine_core_dependent_injector.h"

class EngineCore;
class Entity;

class Component : public EngineCoreDependentInjector {
   public:
    Component(EngineCore *engine_core, bool unique, std::string name = "");
    virtual ~Component() = default;

    inline std::string get_name() const { return this->_name; }
    inline void set_name(std::string name) { this->_name = name; }
    inline bool is_active() const { return this->_active; }
    inline void set_active(bool active) { this->_active = active; }
    inline bool is_unique() const { return this->_unique; }
    inline Entity *get_entity() { return this->_entity_ref; }
    inline void set_entity(Entity *entity) { this->_entity_ref = entity; }
    virtual void on_add_to_entity() = 0;
    virtual void on_remove_from_entity() = 0;
    virtual void on_entity_parent_added(Entity *parent) = 0;
    virtual void on_entity_parent_removed(Entity *parent) = 0;

   private:
    std::string _name;
    bool _active;
    bool _unique;
    Entity *_entity_ref;
};
