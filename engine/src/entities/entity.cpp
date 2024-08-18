#include "../../include/entities/entity.hpp"

#include <algorithm>
#include <cassert>
#include <memory>
#include <utility>
#include <vector>

#include "../../include/components/component.hpp"

Entity::Entity(EngineCore *engine_core, Entity *parent) : EngineCoreDependencyInjector(engine_core) {
    this->_parent = parent;
    this->_children = std::make_unique<ChildrenVector>();
    this->_components = std::make_unique<ComponentsVector>();
}

Entity::Entity(const Entity &other) { this->_copy(other); }

Entity::Entity(Entity &&other) noexcept { this->_move(std::move(other)); }

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
    Entity *child = &this->_children->at(index);

    child->_on_destroy(child);
    this->_on_child_destroy(child);
    child->destroy_all_children();
    this->_children->erase(this->_children->begin() + index);
}

void Entity::destroy_all_children() {
    for (auto it = this->_children->begin(); it != this->_children->end(); ++it) {
        Entity *child = &*it;  // it is converted to Entity and then & gets the address of the Entity :p
        child->_on_destroy(child);
        this->_on_child_destroy(child);
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

Component *Entity::get_component(unsigned int index) const { return this->_components->at(index); }

Component *Entity::get_component(const std::type_info &type_info) const {
    for (auto &component : *this->_components) {
        if (typeid(*component) == type_info) {
            return component;
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
    Component *component = this->_components->at(index);
    component->on_destroy();
    this->_on_component_destroy(this, component);
    component->unregister_component();
    this->_components->erase(this->_components->begin() + index);
}

void Entity::destroy_component(const std::type_info &type_info) {
    unsigned int index = this->get_component_index(type_info);
    this->destroy_component(index);
}

void Entity::destroy_all_components() {
    for (auto &component : *this->_components) {
        component->on_destroy();
        this->_on_component_destroy(this, component);
        component->unregister_component();
    }

    this->_components->clear();
}

Component *Entity::_register_created_component(Component component) {
    if (!component.is_unique() || !this->has_component(typeid(component))) {
        Component *registered_component = component.register_component();

        this->_components->push_back(registered_component);
        this->_on_component_create(this, registered_component);

        return registered_component;
    }

    return nullptr;
}

void Entity::_move(Entity &&other) {
    if (this != &other) {
        this->_children.reset();
        this->_components.reset();

        this->_parent = other._parent;
        this->_children = std::move(other._children);
        this->_components = std::move(other._components);
        this->_on_destroy = other._on_destroy;
        this->_on_child_create = other._on_child_create;
        this->_on_child_destroy = other._on_child_destroy;
        this->_on_component_create = other._on_component_create;
        this->_on_component_destroy = other._on_component_destroy;
    }
}

void Entity::_copy(const Entity &other) {
    if (this != &other) {
        this->_children.reset();
        this->_components.reset();

        this->_parent = other._parent;
        this->_children = std::make_unique<ChildrenVector>(*other._children);
        this->_components = std::make_unique<ComponentsVector>(*other._components);
        this->_on_destroy = other._on_destroy;
        this->_on_child_create = other._on_child_create;
        this->_on_child_destroy = other._on_child_destroy;
        this->_on_component_create = other._on_component_create;
        this->_on_component_destroy = other._on_component_destroy;
    }
}
