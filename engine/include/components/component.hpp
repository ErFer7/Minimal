#pragma once

#include "../types.hpp"
#include "../utils/engine_core_dependency_injector.hpp"
#include "../utils/event.hpp"

// TODO: Implement an activity state
// TODO: Implement name with a hash map

class Component : public EngineCoreDependencyInjector {
    friend class Entity;

   public:
    Component(EngineCore *engine_core, Entity *entity, bool unique = false)
        : EngineCoreDependencyInjector(engine_core), _unique(unique), _entity(entity) {}
    virtual ~Component() = default;

    bool operator==(const Component &other) const { return *this == other; }

    inline bool is_unique() const { return this->_unique; }
    inline Entity *get_entity() const { return this->_entity; }
    inline Event<Component *> *get_on_destroy_event() { return &this->_on_destroy_event; }

   protected:
    virtual void register_component() {};
    virtual void unregister_component() {};

   private:
    bool _unique;
    Entity *_entity;
    Event<Component *> _on_destroy_event;
};
