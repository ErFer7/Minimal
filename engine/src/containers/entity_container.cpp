#include "../../include/containers/entity_container.hpp"

#include "../../include/entities/entity.hpp"

EntityContainer::EntityContainer(EngineCore *engine_core) : EngineCoreDependencyInjector(engine_core) {
    this->_root = this->create_unique<Entity>(nullptr);
}

EntityContainer::~EntityContainer() { this->destroy_all_entities(); }

void EntityContainer::destroy_all_entities() { this->_root->destroy_all_children(); }

void EntityContainer::_register_created_entity(std::unique_ptr<Entity> entity) {
    this->_root->_register_created_child(std::move(entity));
}
