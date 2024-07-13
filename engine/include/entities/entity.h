#pragma once

#include <string>
#include <typeinfo>

#include "../components/component.h"
#include "../components/managed_component.h"
#include "../utils/dynamic_array.hpp"
#include "../utils/engine_core_dependency_injector.h"

class EngineCore;

class Component;

class Entity : public EngineCoreDependencyInjector {
   public:
    Entity() = default;
    Entity(EngineCore *engine_core, bool auto_managed = true);
    ~Entity();

    inline bool is_active() const { return this->_active; }
    inline bool is_auto_managed() const { return this->_auto_managed; }
    inline Entity *get_parent() const { return this->_parent; }
    inline void set_parent(Entity *parent) { this->_parent = parent; }
    inline unsigned int get_child_count() const { return this->_children->get_element_count(); }
    inline DynamicArrayIterator<Entity *> *get_children_iterator() { return new DynamicArrayIterator<Entity *>(this->_children); }
    inline DynamicArrayIterator<Component *> *get_components_iterator() { return new DynamicArrayIterator<Component *>(this->_components); }
    void set_active(bool is_active);
    void set_auto_managed(bool auto_managed);
    void reparent(Entity *parent);
    void add_child(Entity *entity);
    bool has_child(Entity *entity);
    bool has_descendant(Entity *entity);
    Entity *get_child_at(unsigned int index);
    Entity **get_children();
    bool remove_child(Entity *entity);
    bool remove_descendant(Entity *entity);
    bool remove_reference_to_child(Entity *entity);
    bool remove_reference_to_descendant(Entity *entity);
    void remove_all_children();
    void remove_references_to_all_children();
    bool remove();
    bool remove_reference();
    void add_component(Component *component);
    bool has_component(const std::type_info &type_info);
    bool has_component(std::string component_name);
    Component *get_component_at(unsigned int index);
    Component *get_component(const std::type_info &type_info);
    Component *get_component(std::string component_name);
    Component **get_all_components();
    Component **get_components_of_type(const std::type_info &type_info);
    void remove_component(unsigned int index);
    void remove_component(const std::type_info &type_info);
    void remove_component(std::string component_name);
    void remove_all_components();
    void on_parent_add();
    void on_parent_remove();

    template <typename T>
    bool has_component() {
        return this->has_component(typeid(T));
    }

    template <typename T>
    T *get_component() {
        return static_cast<T *>(this->get_component(typeid(T)));
    }

    template <typename T>
    T **get_components_of_type() {
        return static_cast<T **>(this->get_components_of_type(typeid(T)));
    }

    template <typename T>
    void remove_component() {
        this->remove_component(typeid(T));
    }

   private:
    bool _active;
    bool _auto_managed;
    Entity *_parent;  // TODO: Change to shared_ptr<Entity>
    // TODO: Maybe this should be a vector
    DynamicArray<Entity *> *_children;
    DynamicArray<Component *> *_components;
};
