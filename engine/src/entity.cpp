#include "../include/entity.h"

unsigned int Entity::_next_id = 0;

Entity::Entity(std::string name, bool auto_managed) {
    this->_id = _next_id++;
    this->_name = name;
    this->_active = true;
    this->_auto_managed = auto_managed;
    this->_registered = false;
    this->_parent = nullptr;
    this->_children = new DynamicArray<Entity *>(4, 4);
}

Entity::~Entity() { delete this->_children; }

void Entity::set_registered(bool registered) {
    this->_registered = registered;
    this->set_unregistered_descendants(!registered);
}

void Entity::set_unregistered_descendants(bool unregistered_descendants) {
    if (!unregistered_descendants) {
        unsigned int children_with_unregistered_descendants = 0;

        for (unsigned int i = 0; i < this->_children->get_size(); i++) {
            Entity *child = this->_children->raw_at(i);
            if (child != nullptr && (child->has_unregistered_descendants() || !child->is_registered())) {
                children_with_unregistered_descendants++;
            }
        }

        if (children_with_unregistered_descendants > 1) {
            return;
        }
    }

    this->_unregistered_descendants = unregistered_descendants;

    if (this->_parent != nullptr) {
        this->_parent->set_unregistered_descendants(unregistered_descendants);
    }
}

void Entity::set_descendants_marked_for_deletion(bool descendants_marked_for_deletion) {
    this->_descendants_marked_for_deletion = descendants_marked_for_deletion;

    if (this->_parent != nullptr) {
        this->_parent->set_descendants_marked_for_deletion(descendants_marked_for_deletion);
    }
}

void Entity::mark_for_deletion() {
    this->_delete = true;
    this->set_descendants_marked_for_deletion(true);
}

void Entity::set_active(bool is_active) {
    this->_active = is_active;

    for (unsigned int i = 0; i < this->_children->get_size(); i++) {
        if (this->_children->raw_at(i) != nullptr) {
            this->_children->raw_at(i)->set_active(is_active);
        }
    }
}

void Entity::set_parent(Entity *parent) {
    if (this->_parent != nullptr) {
        this->_parent->remove_reference_to_child(this);
    }

    this->_parent = parent;
    this->_parent->add_child(this);
}

void Entity::set_auto_managed(bool auto_managed) {
    this->_auto_managed = auto_managed;

    for (unsigned int i = 0; i < this->_children->get_size(); i++) {
        if (this->_children->raw_at(i) != nullptr) {
            this->_children->raw_at(i)->set_auto_managed(auto_managed);
        }
    }
}

void Entity::add_child(Entity *entity) {
    if (this->has_child(entity->get_id())) {
        return;
    }

    entity->set_parent(this);
    entity->set_active(this->_active);
    entity->set_auto_managed(this->_auto_managed);
    this->set_unregistered_descendants(true);
    this->_children->add(entity);
}

void Entity::register_all_descendants(DynamicArray<Entity *> *entities) {
    for (unsigned int i = 0; i < this->_children->get_size(); i++) {
        Entity *child = this->_children->raw_at(i);

        if (child != nullptr && !child->is_registered()) {
            entities->add(child);
            child->set_registered(true);

            if (child->has_unregistered_descendants()) {
                child->register_all_descendants(entities);
            }
        }
    }
}

bool Entity::has_child(Entity *entity) { return this->_children->contains(entity); }

bool Entity::has_child(unsigned int entity_id) {
    for (unsigned int i = 0; i < this->_children->get_size(); i++) {
        if (this->_children->raw_at(i) != nullptr && this->_children->raw_at(i)->get_id() == entity_id) {
            return true;
        }
    }

    return false;
}

bool Entity::has_child(std::string entity_name) {
    for (unsigned int i = 0; i < this->_children->get_size(); i++) {
        if (this->_children->raw_at(i) != nullptr && this->_children->raw_at(i)->get_name() == entity_name) {
            return true;
        }
    }

    return false;
}

bool Entity::has_descendant(Entity *entity) {
    if (this->has_child(entity)) {
        return true;
    }

    for (unsigned int i = 0; i < this->_children->get_size(); i++) {
        if (this->_children->raw_at(i) != nullptr && this->_children->raw_at(i)->has_descendant(entity)) {
            return true;
        }
    }

    return false;
}

bool Entity::has_descendant(unsigned int entity_id) {
    if (this->has_child(entity_id)) {
        return true;
    }

    for (unsigned int i = 0; i < this->_children->get_size(); i++) {
        if (this->_children->raw_at(i) != nullptr && this->_children->raw_at(i)->has_descendant(entity_id)) {
            return true;
        }
    }

    return false;
}

bool Entity::has_descendant(std::string entity_name) {
    if (this->has_child(entity_name)) {
        return true;
    }

    for (unsigned int i = 0; i < this->_children->get_size(); i++) {
        if (this->_children->raw_at(i) != nullptr && this->_children->raw_at(i)->has_descendant(entity_name)) {
            return true;
        }
    }

    return false;
}

Entity *Entity::get_child_at(unsigned int index) { return this->_children->at(index); }

Entity *Entity::get_child(unsigned int entity_id) {
    for (unsigned int i = 0; i < this->_children->get_size(); i++) {
        if (this->_children->raw_at(i) != nullptr && this->_children->raw_at(i)->get_id() == entity_id) {
            return this->_children->raw_at(i);
        }
    }

    return nullptr;
}

Entity *Entity::get_child(std::string entity_name) {
    for (unsigned int i = 0; i < this->_children->get_size(); i++) {
        if (this->_children->raw_at(i) != nullptr && this->_children->raw_at(i)->get_name() == entity_name) {
            return this->_children->raw_at(i);
        }
    }

    return nullptr;
}

Entity *Entity::get_descendant(unsigned int entity_id) {
    Entity *child = this->get_child(entity_id);

    if (child != nullptr) {
        return child;
    }

    for (unsigned int i = 0; i < this->_children->get_size(); i++) {
        if (this->_children->raw_at(i) != nullptr) {
            Entity *descendant = this->_children->raw_at(i)->get_descendant(entity_id);

            if (descendant != nullptr) {
                return descendant;
            }
        }
    }

    return nullptr;
}

Entity *Entity::get_descendant(std::string entity_name) {
    Entity *child = this->get_child(entity_name);

    if (child != nullptr) {
        return child;
    }

    for (unsigned int i = 0; i < this->_children->get_size(); i++) {
        if (this->_children->raw_at(i) != nullptr) {
            Entity *descendant = this->_children->raw_at(i)->get_descendant(entity_name);

            if (descendant != nullptr) {
                return descendant;
            }
        }
    }

    return nullptr;
}

bool Entity::remove_child(Entity *entity) {
    if (!entity->is_auto_managed()) {
        return false;
    }

    if (this->_children->remove(entity)) {
        entity->mark_for_deletion();
        entity->remove_all_children();

        return true;
    }

    return false;
}

bool Entity::remove_child(unsigned int entity_id) {
    Entity *entity = this->remove_reference_to_child(entity_id);

    if (entity != nullptr && entity->is_auto_managed()) {
        entity->mark_for_deletion();
        entity->remove_all_children();

        return true;
    }

    return false;
}

bool Entity::remove_child(std::string entity_name) {
    Entity *entity = this->remove_reference_to_child(entity_name);

    if (entity != nullptr && entity->is_auto_managed()) {
        entity->mark_for_deletion();
        entity->remove_all_children();

        return true;
    }

    return false;
}

bool Entity::remove_descendant(Entity *entity) {
    if (this->remove_child(entity)) {
        return true;
    }

    for (unsigned int i = 0; i < this->_children->get_size(); i++) {
        if (this->_children->raw_at(i)->remove_descendant(entity)) {
            return true;
        }
    }

    return false;
}

bool Entity::remove_descendant(unsigned int entity_id) {
    if (this->remove_child(entity_id)) {
        return true;
    }

    for (unsigned int i = 0; i < this->_children->get_size(); i++) {
        if (this->_children->raw_at(i)->remove_descendant(entity_id)) {
            return true;
        }
    }

    return false;
}

bool Entity::remove_descendant(std::string entity_name) {
    if (this->remove_child(entity_name)) {
        return true;
    }

    for (unsigned int i = 0; i < this->_children->get_size(); i++) {
        if (this->_children->raw_at(i)->remove_descendant(entity_name)) {
            return true;
        }
    }

    return false;
}

bool Entity::remove_reference_to_child(Entity *entity) { return this->_children->remove(entity); }

Entity *Entity::remove_reference_to_child(unsigned int entity_id) {
    for (unsigned int i = 0; i < this->_children->get_size(); i++) {
        Entity *entity = this->_children->raw_at(i);
        if (entity != nullptr && entity->get_id() == entity_id) {
            this->_children->raw_remove_at(i);
            return entity;
        }
    }

    return nullptr;
}

Entity *Entity::remove_reference_to_child(std::string entity_name) {
    for (unsigned int i = 0; i < this->_children->get_size(); i++) {
        Entity *entity = this->_children->raw_at(i);
        if (entity != nullptr && entity->get_name() == entity_name) {
            this->_children->raw_remove_at(i);
            return entity;
        }
    }

    return nullptr;
}

bool Entity::remove_reference_to_descendant(Entity *entity) {
    if (this->remove_reference_to_child(entity)) {
        return true;
    }

    for (unsigned int i = 0; i < this->_children->get_size(); i++) {
        if (this->_children->raw_at(i)->remove_reference_to_descendant(entity)) {
            return true;
        }
    }

    return false;
}

Entity *Entity::remove_reference_to_descendant(unsigned int entity_id) {
    Entity *child = this->remove_reference_to_child(entity_id);
    if (child != nullptr) {
        return child;
    }

    for (unsigned int i = 0; i < this->_children->get_size(); i++) {
        Entity *descendant = this->_children->raw_at(i)->remove_reference_to_descendant(entity_id);
        if (descendant != nullptr) {
            return descendant;
        }
    }

    return nullptr;
}

Entity *Entity::remove_reference_to_descendant(std::string entity_name) {
    Entity *child = this->remove_reference_to_child(entity_name);
    if (child != nullptr) {
        return child;
    }

    for (unsigned int i = 0; i < this->_children->get_size(); i++) {
        Entity *descendant = this->_children->raw_at(i)->remove_reference_to_descendant(entity_name);
        if (descendant != nullptr) {
            return descendant;
        }
    }

    return nullptr;
}

void Entity::remove_all_children() {
    for (unsigned int i = 0; i < this->_children->get_size(); i++) {
        Entity *child = this->_children->raw_at(i);
        if (child != nullptr && child->is_auto_managed()) {
            child->mark_for_deletion();
            child->remove_all_children();
            this->_children->raw_remove_at(i);
        }
    }
}

void Entity::remove_references_to_all_children() { this->_children->clear(); }

void Entity::remove() {
    if (this->_parent != nullptr) {
        this->_parent->remove_child(this);
    }
}

void Entity::remove_reference() {
    if (this->_parent != nullptr) {
        this->_parent->remove_reference_to_child(this);
    }
}
