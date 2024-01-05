#include "../include/entity_manager.h"

EntityManager::EntityManager() {
    this->_root = new Entity("Global Root");
    this->_entities = new DynamicArray<Entity *>(128, 16);

    this->_entities->add(this->_root);
    this->_root->set_registered(true);
}

EntityManager::~EntityManager() {
    this->remove_all_entities();

    delete this->_root;
    delete this->_entities;
}

Entity *EntityManager::find_entity(unsigned int entity_id) {
    for (unsigned int i = 0; i < this->_entities->get_size(); i++) {
        Entity *entity = this->_entities->raw_at(i);
        if (entity != nullptr && entity->get_id() == entity_id) {
            return entity;
        }
    }

    return nullptr;
}

Entity *EntityManager::find_entity(std::string entity_name) {
    for (unsigned int i = 0; i < this->_entities->get_size(); i++) {
        Entity *entity = this->_entities->raw_at(i);
        if (entity != nullptr && entity->get_name() == entity_name) {
            return entity;
        }
    }

    return nullptr;
}

bool EntityManager::remove_entity(Entity *entity) {
    if (!entity->is_auto_managed()) {
        return false;
    }

    this->_entities->remove(entity);
    delete entity;

    return true;
}

bool EntityManager::remove_entity(unsigned int entity_id) {
    Entity *entity = this->find_entity(entity_id);

    if (entity != nullptr && entity->is_auto_managed()) {
        return this->remove_entity(entity);
    }

    return false;
}

bool EntityManager::remove_entity(std::string entity_name) {
    Entity *entity = this->find_entity(entity_name);

    if (entity != nullptr && entity->is_auto_managed()) {
        return this->remove_entity(entity);
    }

    return false;
}

void EntityManager::update() {
    if (this->_root->has_descendants_marked_for_deletion()) {
        for (unsigned int i = 0; i < this->_entities->get_size(); i++) {
            Entity *entity = this->_entities->raw_at(i);

            entity->set_descendants_marked_for_deletion(false);

            if (entity != nullptr && entity->should_delete()) {
                delete entity;
                this->_entities->raw_remove_at(i);
            }
        }
    }

    if (this->_root->has_unregistered_descendants()) {
        this->_root->register_all_descendants(this->_entities);
    }
}
