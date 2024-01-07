#include "../include/entity_manager.h"

EntityManager::EntityManager() {
    this->_root = new Entity("Global Root");
    this->_entities = new DynamicArray<Entity *>(128, 16);
    this->_temp_components = new DynamicArray<Component *>(256, 32);

    this->_entities->add(this->_root);
    this->_root->set_registered(true);
}

EntityManager::~EntityManager() {
    this->remove_all_entities();

    if (this->_root != nullptr) {
        delete this->_root;
        this->_root = nullptr;
    }

    if (this->_entities != nullptr) {
        delete this->_entities;
        this->_entities = nullptr;
    }
}

Entity *EntityManager::find_entity(unsigned int entity_id) {
    for (unsigned int i = 0; i < this->_entities->get_size(); i++) {
        Entity *entity = this->_entities->nullable_at(i);
        if (entity != nullptr && entity->get_id() == entity_id) {
            return entity;
        }
    }

    return nullptr;
}

Entity *EntityManager::find_entity(std::string entity_name) {
    for (unsigned int i = 0; i < this->_entities->get_size(); i++) {
        Entity *entity = this->_entities->nullable_at(i);
        if (entity != nullptr && entity->get_name() == entity_name) {
            return entity;
        }
    }

    return nullptr;
}

bool EntityManager::remove_entity(unsigned int entity_id) {
    Entity *entity = this->find_entity(entity_id);

    return entity->remove();
}

bool EntityManager::remove_entity(std::string entity_name) {
    Entity *entity = this->find_entity(entity_name);

    return entity->remove();
}

void EntityManager::update() {
    if (this->_root->has_unregistered_descendants()) {
        this->_root->register_all_descendants(
            this->_entities, std::bind(&EntityManager::_on_entity_remove, this, std::placeholders::_1));
    }

    if (this->_root->has_descendants_with_unregistered_components()) {
        this->_root->register_all_descendants_components(
            this->_temp_components, std::bind(&EntityManager::_on_temp_component_remove, this, std::placeholders::_1));
    }

    this->_entities->optimize();
    this->_temp_components->optimize();
}

void EntityManager::_on_entity_remove(Entity *entity) { this->_entities->remove(entity, false); }

void EntityManager::_on_temp_component_remove(Component *component) { this->_temp_components->remove(component, false); }
