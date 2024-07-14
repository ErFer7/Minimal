#include "../../include/entities/entity.h"

#include <algorithm>
#include <cassert>
#include <memory>
#include <utility>
#include <vector>

Entity::Entity(EngineCore *engine_core, Entity *parent) : EngineCoreDependencyInjector(engine_core) {
    this->_active = true;
    this->_ancestor_active = true;
    this->_parent = nullptr;
    this->_children = std::make_unique<ChildrenVector>();
    this->_components = std::make_unique<ComponentsVector>();

    this->set_parent(parent);
}

Entity::~Entity() {
    this->destroy_all_children();
    this->remove_all_components();
}

void Entity::set_active(bool is_active) {
    this->_active = is_active;

    for (auto &child : *this->_children) {
        if (child != nullptr) {
            child->_set_ancestor_active(is_active);
        }
    }
}

void Entity::set_parent(Entity *parent) {
    std::unique_ptr<Entity> child;

    if (this->_parent != nullptr) {
        unsigned int index = this->_parent->get_child_index(this);
        child = std::move(this->_parent->_children->at(index));
        // TODO: Call an event here
        this->_parent->_children->erase(this->_children->begin() + index);
    }

    this->_parent = parent;
    this->_parent->_children->push_back(child);
}

bool Entity::has_child(Entity *entity) {
    return std::find(this->_children->begin(), this->_children->end(), entity) != this->_children->end();
}

unsigned int Entity::get_child_index(Entity *entity) {
    auto it = std::find(this->_children->begin(), this->_children->end(), entity);

    if (it != this->_children->end()) {
        return std::distance(this->_children->begin(), it);
    }

    return -1;
}

bool Entity::has_descendant(Entity *entity) {
    if (this->has_child(entity)) {
        return true;
    }

    for (auto &child : *this->_children) {
        if (child->has_descendant(entity)) {
            return true;
        }
    }

    return false;
}

void Entity::destroy_child(unsigned int index) {
    Entity *child = this->_children->at(index).get();
    child->on_parent_remove();
    child->destroy_all_children();
    this->_children->erase(this->_children->begin() + index);
}

void Entity::destroy_all_children() {
    for (auto &child : *this->_children) {
        child->on_parent_remove();
        child->destroy_all_children();
    }

    this->_children->clear();
}

void Entity::destroy() {
    if (this->_parent != nullptr) {
        this->_parent->destroy_child(this->_parent->get_child_index(this));
    }
}

void Entity::add_component(Component *component) {
    if (!component->is_unique() || !this->has_component(typeid(*component))) {
        component->set_entity(this);

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
        if (this->_components->nullable_at(i) != nullptr && this->_components->nullable_at(i)->get_name() == component_name) {
            return true;
        }
    }

    return false;
}

Component *Entity::get_component_at(unsigned int index) { return this->_components->at(index); }

Component *Entity::get_component(const std::type_info &type_info) {
    for (unsigned int i = 0; i < this->_components->get_size(); i++) {
        if (this->_components->nullable_at(i) != nullptr && typeid(*this->_components->nullable_at(i)) == type_info) {
            return this->_components->nullable_at(i);
        }
    }

    return nullptr;
}

Component *Entity::get_component(std::string component_name) {
    for (unsigned int i = 0; i < this->_components->get_size(); i++) {
        if (this->_components->nullable_at(i) != nullptr && this->_components->nullable_at(i)->get_name() == component_name) {
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
            this->_components->nullable_remove_at(i);
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

void Entity::_set_ancestor_active(bool ancestor_active) {
    this->_ancestor_active = ancestor_active;

    for (auto &child : *this->_children) {
        if (child != nullptr) {
            child->set_ancestor_active(ancestor_active);
        }
    }
}
