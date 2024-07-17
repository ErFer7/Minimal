#include "../../include/entities/entity.hpp"

#include <algorithm>
#include <cassert>
#include <memory>
#include <utility>
#include <vector>

#include "../../include/components/component.hpp"
#include "../../include/components/managed_component.hpp"

Entity::Entity(EngineCore *engine_core, Entity *parent) : EngineCoreDependencyInjector(engine_core) {
    this->_parent = parent;
    this->_children = std::make_unique<ChildrenVector>();
    this->_components = std::make_unique<ComponentsVector>();
}

Entity::~Entity() {
    this->destroy_all_children();
    this->destroy_all_components();
}

const unsigned int Entity::get_child_index(Entity *entity) const {
    auto it = std::find(this->_children->begin(), this->_children->end(), entity);

    if (it != this->_children->end()) {
        return std::distance(this->_children->begin(), it);
    }

    return -1;
}

void Entity::destroy_child(unsigned int index) {
    Entity *child = this->_children->at(index).get();
    child->_on_destroy(child);
    this->_on_child_destroy(child);
    child->destroy_all_children();
    this->_children->erase(this->_children->begin() + index);
}

void Entity::destroy_all_children() {
    for (auto &child : *this->_children) {
        child->_on_destroy(child.get());
        this->_on_child_destroy(child.get());
        child->destroy_all_children();
    }

    this->_children->clear();
}

void Entity::destroy() {
    assert(this->_parent != nullptr);

    this->_parent->destroy_child(this->_parent->get_child_index(this));
}

bool Entity::has_component(const std::type_info &type_info) const {
    for (auto &component : *this->_components) {
        if (typeid(*component) == type_info) {
            return true;
        }
    }

    return false;
}

Component *Entity::get_component(unsigned int index) const { return this->_components->at(index).get(); }

Component *Entity::get_component(const std::type_info &type_info) const {
    for (auto &component : *this->_components) {
        if (typeid(*component) == type_info) {
            return component.get();
        }
    }

    return nullptr;
}

const unsigned int Entity::get_component_index(Component *component) const {
    auto it = std::find(this->_components->begin(), this->_components->end(), component);

    if (it != this->_components->end()) {
        return std::distance(this->_components->begin(), it);
    }

    return -1;
}

const unsigned int Entity::get_component_index(const std::type_info &type_info) const {
    unsigned int index = 0;

    for (auto &component : *this->_components) {
        if (typeid(*component) == type_info) {
            return index;
        }

        index++;
    }

    return -1;
}

void Entity::destroy_component(unsigned int index) {
    Component *component = this->_components->at(index).get();
    component->on_destroy();
    this->_on_component_destroy(this, component);

    if (static_cast<ManagedComponent *>(component) != nullptr) {
        ManagedComponent *managed_component = static_cast<ManagedComponent *>(component);
        managed_component->unregister_component();
    }

    this->_components->erase(this->_components->begin() + index);
}

void Entity::destroy_component(const std::type_info &type_info) {
    unsigned int index = this->get_component_index(type_info);
    this->destroy_component(index);
}

void Entity::destroy_all_components() {
    for (auto &component : *this->_components) {
        component->on_destroy();
        this->_on_component_destroy(this, component.get());

        if (static_cast<ManagedComponent *>(component.get()) != nullptr) {
            ManagedComponent *managed_component = static_cast<ManagedComponent *>(component.get());
            managed_component->unregister_component();
        }
    }

    this->_components->clear();
}

Entity *Entity::_register_created_child(std::unique_ptr<Entity> child) {
    this->_children->push_back(child);
    this->_on_child_create(child.get());

    return this->_children->back().get();
}

Component *Entity::_register_created_component(std::unique_ptr<Component> component) {
    if (!component->is_unique() || !this->has_component(typeid(*component))) {
        if (static_cast<ManagedComponent *>(component.get()) != nullptr) {
            ManagedComponent *managed_component = static_cast<ManagedComponent *>(component.get());
            managed_component->register_component();
        }

        this->_components->push_back(std::move(component));
        this->_on_component_create(this, component.get());

        return this->_components->back().get();
    }

    return nullptr;
}
