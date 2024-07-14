#include "../../include/containers/entity_container.h"

EntityContainer::EntityContainer(EngineCore *engine_core) : EngineCoreDependencyInjector(engine_core) {
    this->_root = this->create_unique<Entity>(nullptr);
}

EntityContainer::~EntityContainer() { this->destroy_all_entities(); }

void EntityContainer::create_entity(Entity *entity) { this->_root->create_child(entity); }

void EntityContainer::destroy_all_entities() { this->_root->destroy_all_children(); }
