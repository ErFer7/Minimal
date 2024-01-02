#include "../include/entity_container.h"

EntityContainer::EntityContainer() { this->_entity_groups = new EntityGroups(); }

EntityContainer::~EntityContainer() {
    for (auto &entity_group_pair : *this->_entity_groups) {
        delete entity_group_pair.second;
    }

    this->_entity_groups->clear();
    delete this->_entity_groups;
}

void EntityContainer::create_entity_group(const std::string &group_name) {
    EntityGroup *entity_group = new EntityGroup();
    (*this->_entity_groups)[group_name] = entity_group;
}

void EntityContainer::add_entity_to_group(const std::string &group_name, Entity *entity) {
    (*this->_entity_groups)[group_name]->add_entity(entity);
}

void EntityContainer::remove_entity_from_group(const std::string &group_name, Entity *entity) {
    (*this->_entity_groups)[group_name]->remove_entity(entity);
}

void EntityContainer::clear_entity_group(const std::string &group_name) {}

void EntityContainer::delete_entity_group(const std::string &group_name) {
    delete (*this->_entity_groups)[group_name];
    this->_entity_groups->erase(group_name);
}
