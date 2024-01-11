#pragma once

#include <string>

class EngineCore;
class Entity;

class Component {
   public:
    Component(bool unique, std::string name = "");
    virtual ~Component() = default;
    inline std::string get_name() const { return this->_name; }
    inline void set_name(std::string name) { this->_name = name; }
    inline bool is_active() const { return this->_active; }
    inline void set_active(bool active) { this->_active = active; }
    inline bool is_unique() const { return this->_unique; }
    inline EngineCore *get_engine_core() { return this->_engine_core; }
    inline void set_engine_core(EngineCore *engine_core) { this->_engine_core = engine_core; }
    inline Entity *get_entity() { return this->_entity; }
    inline void set_entity(Entity *entity) { this->_entity = entity; }
    virtual void on_add_to_entity() = 0;
    virtual void on_remove_from_entity() = 0;
    virtual void on_entity_parent_added(Entity *parent) = 0;
    virtual void on_entity_parent_removed(Entity *parent) = 0;

   private:
    std::string _name;
    bool _active;
    bool _unique;
    EngineCore *_engine_core;
    Entity *_entity;
};
