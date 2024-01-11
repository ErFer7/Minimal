#include "../../include/entities/entity.h"
#include <iostream>

unsigned int Entity::_next_id = 0;

Entity::Entity(std::string name, bool auto_managed) {
    this->_id = _next_id++;
    this->_name = name;
    this->_active = true;
    this->_auto_managed = auto_managed;
    this->_parent = nullptr;
    this->_children = new DynamicArray<Entity *>(4, 4);
    this->_components = new DynamicArray<Component *>(2, 2);
}

Entity::~Entity() {
    this->remove_all_children();
    this->remove_all_components();

    if (this->_children != nullptr) {
        delete this->_children;
        this->_children = nullptr;
    }

    if (this->_components != nullptr) {
        delete this->_components;
        this->_components = nullptr;
    }
}

void Entity::set_active(bool is_active) {
    this->_active = is_active;

    for (unsigned int i = 0; i < this->_children->get_size(); i++) {
        if (this->_children->nullable_at(i) != nullptr) {
            this->_children->nullable_at(i)->set_active(is_active);
        }
    }
}

void Entity::reparent(Entity *parent) {
    if (this->_parent != nullptr) {
        this->_parent->remove_reference_to_child(this);
    }

    this->_parent = parent;
    this->_parent->add_child(this);
}

void Entity::set_auto_managed(bool auto_managed) {
    this->_auto_managed = auto_managed;

    for (unsigned int i = 0; i < this->_children->get_size(); i++) {
        if (this->_children->nullable_at(i) != nullptr) {
            this->_children->nullable_at(i)->set_auto_managed(auto_managed);
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
    entity->set_engine_core(this->_engine_core);
    this->_children->add(entity);

    entity->on_parent_add();
}

bool Entity::has_child(Entity *entity) { return this->_children->contains(entity); }

bool Entity::has_child(unsigned int entity_id) {
    for (unsigned int i = 0; i < this->_children->get_size(); i++) {
        if (this->_children->nullable_at(i) != nullptr && this->_children->nullable_at(i)->get_id() == entity_id) {
            return true;
        }
    }

    return false;
}

bool Entity::has_child(std::string entity_name) {
    for (unsigned int i = 0; i < this->_children->get_size(); i++) {
        if (this->_children->nullable_at(i) != nullptr && this->_children->nullable_at(i)->get_name() == entity_name) {
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
        if (this->_children->nullable_at(i) != nullptr && this->_children->nullable_at(i)->has_descendant(entity)) {
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
        if (this->_children->nullable_at(i) != nullptr && this->_children->nullable_at(i)->has_descendant(entity_id)) {
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
        if (this->_children->nullable_at(i) != nullptr &&
            this->_children->nullable_at(i)->has_descendant(entity_name)) {
            return true;
        }
    }

    return false;
}

Entity *Entity::get_child_at(unsigned int index) {
    if (index >= this->_children->get_element_count()) {
        return nullptr;
    }

    unsigned int counted_index = 0;

    for (unsigned int i = 0; i < this->_children->get_size(); i++) {
        if (this->_children->nullable_at(i) != nullptr) {
            if (counted_index == index) {
                return this->_children->nullable_at(i);
            }

            counted_index++;
        }
    }

    return nullptr;
}

Entity *Entity::get_child(unsigned int entity_id) {
    for (unsigned int i = 0; i < this->_children->get_size(); i++) {
        if (this->_children->nullable_at(i) != nullptr && this->_children->nullable_at(i)->get_id() == entity_id) {
            return this->_children->nullable_at(i);
        }
    }

    return nullptr;
}

Entity *Entity::get_child(std::string entity_name) {
    for (unsigned int i = 0; i < this->_children->get_size(); i++) {
        if (this->_children->nullable_at(i) != nullptr && this->_children->nullable_at(i)->get_name() == entity_name) {
            return this->_children->nullable_at(i);
        }
    }

    return nullptr;
}

Entity **Entity::get_children() { return this->_children->get_elements(); }

Entity *Entity::get_descendant(unsigned int entity_id) {
    Entity *child = this->get_child(entity_id);

    if (child != nullptr) {
        return child;
    }

    for (unsigned int i = 0; i < this->_children->get_size(); i++) {
        if (this->_children->nullable_at(i) != nullptr) {
            Entity *descendant = this->_children->nullable_at(i)->get_descendant(entity_id);

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
        if (this->_children->nullable_at(i) != nullptr) {
            Entity *descendant = this->_children->nullable_at(i)->get_descendant(entity_name);

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

    entity->on_parent_remove();

    if (this->_children->remove(entity)) {
        entity->remove_all_children();
        delete entity;

        return true;
    }

    return false;
}

bool Entity::remove_child(unsigned int entity_id) {
    Entity *entity = this->remove_reference_to_child(entity_id);

    if (entity != nullptr && entity->is_auto_managed()) {
        entity->remove_all_children();
        delete entity;

        return true;
    }

    return false;
}

bool Entity::remove_child(std::string entity_name) {
    Entity *entity = this->remove_reference_to_child(entity_name);

    if (entity != nullptr && entity->is_auto_managed()) {
        entity->remove_all_children();
        delete entity;

        return true;
    }

    return false;
}

bool Entity::remove_descendant(Entity *entity) {
    if (this->remove_child(entity)) {
        return true;
    }

    for (unsigned int i = 0; i < this->_children->get_size(); i++) {
        if (this->_children->nullable_at(i)->remove_descendant(entity)) {
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
        if (this->_children->nullable_at(i)->remove_descendant(entity_id)) {
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
        if (this->_children->nullable_at(i)->remove_descendant(entity_name)) {
            return true;
        }
    }

    return false;
}

bool Entity::remove_reference_to_child(Entity *entity) {
    entity->on_parent_remove();

    return this->_children->remove(entity);
}

Entity *Entity::remove_reference_to_child(unsigned int entity_id) {
    for (unsigned int i = 0; i < this->_children->get_size(); i++) {
        Entity *entity = this->_children->nullable_at(i);
        if (entity != nullptr && entity->get_id() == entity_id) {
            entity->on_parent_remove();
            this->_children->nullable_remove_at(i);
            return entity;
        }
    }

    return nullptr;
}

Entity *Entity::remove_reference_to_child(std::string entity_name) {
    for (unsigned int i = 0; i < this->_children->get_size(); i++) {
        Entity *entity = this->_children->nullable_at(i);
        if (entity != nullptr && entity->get_name() == entity_name) {
            entity->on_parent_remove();
            this->_children->nullable_remove_at(i);
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
        if (this->_children->nullable_at(i)->remove_reference_to_descendant(entity)) {
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
        Entity *descendant = this->_children->nullable_at(i)->remove_reference_to_descendant(entity_id);
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
        Entity *descendant = this->_children->nullable_at(i)->remove_reference_to_descendant(entity_name);
        if (descendant != nullptr) {
            return descendant;
        }
    }

    return nullptr;
}

void Entity::remove_all_children() {
    for (unsigned int i = 0; i < this->_children->get_size(); i++) {
        Entity *child = this->_children->nullable_at(i);
        if (child != nullptr && child->is_auto_managed()) {
            child->on_parent_remove();
            child->remove_all_children();
            delete child;
        }
    }

    this->_children->clear();
}

void Entity::remove_references_to_all_children() {
    for (unsigned int i = 0; i < this->_children->get_size(); i++) {
        Entity *child = this->_children->nullable_at(i);
        if (child != nullptr) {
            child->on_parent_remove();
        }
    }

    this->_children->clear();
}

bool Entity::remove() {
    if (this->_parent != nullptr) {
        return this->_parent->remove_child(this);
    }

    return false;
}

bool Entity::remove_reference() {
    if (this->_parent != nullptr) {
        return this->_parent->remove_reference_to_child(this);
    }

    return false;
}

void Entity::add_component(Component *component) {
    if (component->is_unique() && !this->has_component(typeid(*component))) {
        component->set_entity(this);
        component->set_engine_core(this->_engine_core);

        if (dynamic_cast<ManagedComponent *>(component) != nullptr) {
            ManagedComponent *managed_component = static_cast<ManagedComponent *>(component);
            managed_component->register_component();
        }

        this->_components->add(component);
        component->on_add_to_entity();
    }
}

bool Entity::has_component(const std::type_info &type_info) {
    for (unsigned int i = 0; i < this->_components->get_size(); i++) {
        if (this->_components->nullable_at(i) != nullptr && typeid(*this->_components->nullable_at(i)) == type_info) {
            return true;
        }
    }

    return false;
}

bool Entity::has_component(std::string component_name) {
    for (unsigned int i = 0; i < this->_components->get_size(); i++) {
        if (this->_components->nullable_at(i) != nullptr &&
            this->_components->nullable_at(i)->get_name() == component_name) {
            return true;
        }
    }

    return false;
}

Component *Entity::get_component_at(unsigned int index) { return this->_components->at(index); }

Component *Entity::get_component(const std::type_info &type_info) {
    for (unsigned int i = 0; i < this->_components->get_size(); i++) {
        if (this->_components->nullable_at(i) != nullptr && typeid(*this->_components->nullable_at(i)) == type_info) {
            std::cout << "Found component of type " << type_info.name() << std::endl;
            std::cout << "Entity name: " << this->_name << std::endl;
            return this->_components->nullable_at(i);
        }
    }

    return nullptr;
}

Component *Entity::get_component(std::string component_name) {
    for (unsigned int i = 0; i < this->_components->get_size(); i++) {
        if (this->_components->nullable_at(i) != nullptr &&
            this->_components->nullable_at(i)->get_name() == component_name) {
            return this->_components->nullable_at(i);
        }
    }

    return nullptr;
}

Component **Entity::get_all_components() { return this->_components->get_elements(); }

Component **Entity::get_components_of_type(const std::type_info &type_info) {
    Component **components = new Component *[this->_components->get_element_count()];

    unsigned int counted_index = 0;

    for (unsigned int i = 0; i < this->_components->get_size(); i++) {
        if (this->_components->nullable_at(i) != nullptr && typeid(*this->_components->nullable_at(i)) == type_info) {
            components[counted_index] = this->_components->nullable_at(i);
            counted_index++;
        }
    }

    return components;
}

void Entity::remove_component(unsigned int index) {
    Component *component = this->_components->at(index);
    component->on_remove_from_entity();

    if (dynamic_cast<ManagedComponent *>(component) != nullptr) {
        ManagedComponent *managed_component = static_cast<ManagedComponent *>(component);
        managed_component->unregister_component();
    }

    delete component;
    this->_components->remove_at(index);
}

void Entity::remove_component(const std::type_info &type_info) {
    for (unsigned int i = 0; i < this->_components->get_size(); i++) {
        Component *component = this->_components->nullable_at(i);

        if (component != nullptr && typeid(*component) == type_info) {
            component->on_remove_from_entity();

            if (dynamic_cast<ManagedComponent *>(component) != nullptr) {
                ManagedComponent *managed_component = static_cast<ManagedComponent *>(component);
                managed_component->unregister_component();
            }

            delete component;
            this->_components->nullable_remove_at(i);
            return;
        }
    }
}

void Entity::remove_component(std::string component_name) {
    for (unsigned int i = 0; i < this->_components->get_size(); i++) {
        Component *component = this->_components->nullable_at(i);

        if (component != nullptr && component->get_name() == component_name) {
            component->on_remove_from_entity();

            if (dynamic_cast<ManagedComponent *>(component) != nullptr) {
                ManagedComponent *managed_component = static_cast<ManagedComponent *>(component);
                managed_component->unregister_component();
            }

            delete component;
            this->_components->nullable_remove_at(i);
            return;
        }
    }
}

void Entity::remove_all_components() {
    for (unsigned int i = 0; i < this->_components->get_size(); i++) {
        Component *component = this->_components->nullable_at(i);

        if (component != nullptr) {
            component->on_remove_from_entity();

            if (dynamic_cast<ManagedComponent *>(component) != nullptr) {
                ManagedComponent *managed_component = static_cast<ManagedComponent *>(component);
                managed_component->unregister_component();
            }

            delete component;
        }
    }

    this->_components->clear();
}

void Entity::on_parent_add() {
    for (unsigned int i = 0; i < this->_components->get_size(); i++) {
        Component *component = this->_components->nullable_at(i);

        if (component != nullptr) {
            component->on_entity_parent_added(this->_parent);
        }
    }
}

void Entity::on_parent_remove() {
    for (unsigned int i = 0; i < this->_components->get_size(); i++) {
        Component *component = this->_components->nullable_at(i);

        if (component != nullptr) {
            component->on_entity_parent_removed(this->_parent);
        }
    }
}
