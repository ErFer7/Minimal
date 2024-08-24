#include "../../include/entities/entity.hpp"

#include <algorithm>
#include <cassert>
#include <memory>
#include <vector>

#include "../../include/components/component.hpp"

Entity::Entity(EngineCore *engine_core, Entity *parent) : EngineCoreDependencyInjector(engine_core) {
    this->_parent = parent;
    this->_children = std::make_unique<ChildrenVector>();
    this->_components = std::make_unique<ComponentsVector>();
}

Entity::~Entity() {
    this->destroy_all_children();
    this->destroy_all_components();
}

unsigned int Entity::get_child_index(Entity *entity) const {
    auto it = std::find(this->_children->begin(), this->_children->end(), std::unique_ptr<Entity>(entity));

    if (it != this->_children->end()) {
        return std::distance(this->_children->begin(), it);
    }

    return -1;
}

void Entity::destroy_child(unsigned int index) {
    Entity *child = this->_children->at(index).get();

    child->get_on_destroy_event().invoke(child);
    this->_on_child_destroy_event.invoke(child);
    child->destroy_all_children();
    this->_children->erase(this->_children->begin() + index);
}

void Entity::destroy_all_children() {
    assert(this->_children != nullptr);

    for (auto it = this->_children->begin(); it != this->_children->end(); ++it) {
        Entity *child = it->get();
        child->get_on_destroy_event().invoke(child);
        this->_on_child_destroy_event.invoke(child);
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

unsigned int Entity::get_component_index(Component *component) const {
    auto it = std::find(this->_components->begin(), this->_components->end(), std::unique_ptr<Component>(component));

    if (it != this->_components->end()) {
        return std::distance(this->_components->begin(), it);
    }

    return -1;
}

unsigned int Entity::get_component_index(const std::type_info &type_info) const {
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
    component->get_on_destroy_event()->invoke(component);
    this->_on_component_destroy_event.invoke(this, component);
    component->unregister_component();
    this->_components->erase(this->_components->begin() + index);
}

void Entity::destroy_component(const std::type_info &type_info) {
    unsigned int index = this->get_component_index(type_info);
    this->destroy_component(index);
}

void Entity::destroy_all_components() {
    for (auto &component : *this->_components) {
        component->get_on_destroy_event()->invoke(component.get());
        this->_on_component_destroy_event.invoke(this, component.get());
        component->unregister_component();
    }

    this->_components->clear();
}

Component *Entity::_register_created_component(std::unique_ptr<Component> component) {
    if (!component->is_unique() || !this->has_component(typeid(component))) {
        this->_components->push_back(std::move(component));

        Component *component_raw_ref = this->_components->back().get();

        component_raw_ref->register_component();
        this->_on_component_create_event.invoke(this, component_raw_ref);

        return component_raw_ref;
    }

    return nullptr;
}
