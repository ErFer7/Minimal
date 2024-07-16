#pragma once

#include "../types.hpp"
#include "../utils/engine_core_dependency_injector.hpp"

class Component : public EngineCoreDependencyInjector {
    friend class Entity;

   public:
    Component(EngineCore *engine_core, Entity *entity, bool unique);
    virtual ~Component() = default;

    const bool is_active() const;
    inline const bool is_set_as_active() const { return this->_active; }
    inline void set_active(bool active) { this->_active = active; }
    inline const bool is_unique() const { return this->_unique; }
    inline Entity *get_entity() const { return this->_entity; }
    virtual void on_destroy() = 0;
    virtual void on_entity_parent_changed(Entity *old_parent, Entity *new_parent) = 0;

   private:
    bool _active;
    bool _unique;
    Entity *_entity;
};
