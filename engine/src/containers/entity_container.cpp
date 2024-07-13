#include "../../include/containers/entity_container.h"

EntityContainer::EntityContainer(EngineCore *engine_core) : EngineCoreDependencyInjector(engine_core) {
    this->_root = this->create_on_stack<Entity>();
}

EntityContainer::~EntityContainer() { this->remove_all_entities(); }

void EntityContainer::add_entity(Entity *entity) { this->_root.add_child(entity); }

void EntityContainer::remove_all_entities() { this->_root.remove_all_children(); }

