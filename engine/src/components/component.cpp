#include "../../include/components/component.hpp"

#include "../../include/entities/entity.hpp"

Component::Component(EngineCore *engine_core, Entity *entity, bool unique) : EngineCoreDependencyInjector(engine_core) {
    this->_active = true;
    this->_unique = unique;
    this->_entity = entity;
}

const bool Component::is_active() const { return this->_entity->is_active() && this->_active; }
