#include "../../include/containers/entity_container.h"

EntityContainer::EntityContainer(EngineCore *engine_core) {
    this->_root = new Entity("Global Root");
    this->_root->set_engine_core(engine_core);
}

EntityContainer::~EntityContainer() {
    this->remove_all_entities();

    if (this->_root != nullptr) {
        delete this->_root;
        this->_root = nullptr;
    }
}

void EntityContainer::add_entity(Entity *entity) { this->_root->add_child(entity); }

void EntityContainer::remove_all_entities() { this->_root->remove_all_children(); }

Entity *EntityContainer::find_entity(unsigned int entity_id) { return this->_root->get_descendant(entity_id); }

Entity *EntityContainer::find_entity(std::string entity_name) { return this->_root->get_descendant(entity_name); }

bool EntityContainer::remove_entity(unsigned int entity_id) { return this->_root->remove_descendant(entity_id); }

bool EntityContainer::remove_entity(std::string entity_name) { return this->_root->remove_descendant(entity_name); }
