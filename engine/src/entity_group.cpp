#include "../include/entity_group.h"

EntityGroup::EntityGroup() { this->_entities = new Entities(); }

EntityGroup::~EntityGroup() {
    for (auto &entity_pair : *this->_entities) {
        if (entity_pair.second->is_auto_managed()) {
            delete entity_pair.second;
        }
    }

    this->_entities->clear();
    delete this->_entities;
}

void EntityGroup::add_entity(Entity *entity) { (*this->_entities)[entity->get_id()] = entity; }

void EntityGroup::remove_entity(Entity *entity) {
    delete (*this->_entities)[entity->get_id()];
    this->_entities->erase(entity->get_id());
}

void EntityGroup::clear_entities() {
    for (auto &entity_pair : *this->_entities) {
        if (entity_pair.second->is_auto_managed()) {
            delete entity_pair.second;
        }
    }

    this->_entities->clear();
}