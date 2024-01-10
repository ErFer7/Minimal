#pragma once

#include <string>
#include <typeinfo>

#include "../components/component.h"
#include "../components/managed_component.h"
#include "../utils/dynamic_array.h"

class EngineCore;

class Component;

class Entity {
   public:
    Entity(std::string name = "", bool auto_managed = true);
    ~Entity();
    inline unsigned int get_id() { return this->_id; }
    inline bool is_active() const { return this->_active; }
    inline bool is_auto_managed() const { return this->_auto_managed; }
    inline std::string get_name() const { return this->_name; }
    inline void set_name(std::string name) { this->_name = name; }
    inline Entity *get_parent() const { return this->_parent; }
    inline void set_parent(Entity *parent) { this->_parent = parent; }
    inline unsigned int get_child_count() const { return this->_children->get_element_count(); }
    inline DynamicArrayIterator<Entity *> *get_children_iterator() {
        return new DynamicArrayIterator<Entity *>(this->_children);
    }
    inline DynamicArrayIterator<Component *> *get_components_iterator() {
        return new DynamicArrayIterator<Component *>(this->_components);
    }
    inline EngineCore *get_engine_core() { return this->_engine_core; }
    inline void set_engine_core(EngineCore *engine_core) { this->_engine_core = engine_core; }
    void set_active(bool is_active);
    void set_auto_managed(bool auto_managed);
    void reparent(Entity *parent);
    void add_child(Entity *entity);
    bool has_child(Entity *entity);
    bool has_child(unsigned int entity_id);
    bool has_child(std::string entity_name);
    bool has_descendant(Entity *entity);
    bool has_descendant(unsigned int entity_id);
    bool has_descendant(std::string entity_name);
    Entity *get_child_at(unsigned int index);
    Entity *get_child(unsigned int entity_id);
    Entity *get_child(std::string entity_name);
    Entity **get_children();
    Entity *get_descendant(unsigned int entity_id);
    Entity *get_descendant(std::string entity_name);
    bool remove_child(Entity *entity);
    bool remove_child(unsigned int entity_id);
    bool remove_child(std::string entity_name);
    bool remove_descendant(Entity *entity);
    bool remove_descendant(unsigned int entity_id);
    bool remove_descendant(std::string entity_name);
    bool remove_reference_to_child(Entity *entity);
    Entity *remove_reference_to_child(unsigned int entity_id);
    Entity *remove_reference_to_child(std::string entity_name);
    bool remove_reference_to_descendant(Entity *entity);
    Entity *remove_reference_to_descendant(unsigned int entity_id);
    Entity *remove_reference_to_descendant(std::string entity_name);
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
    static unsigned int _next_id;
    unsigned int _id;
    std::string _name;
    bool _active;
    bool _auto_managed;
    Entity *_parent;
    DynamicArray<Entity *> *_children;
    DynamicArray<Component *> *_components;
    EngineCore *_engine_core;
};
