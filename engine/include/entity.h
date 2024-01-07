#pragma once

#include <functional>
#include <string>
#include <typeinfo>

#include "component.h"
#include "dynamic_array.h"

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
    inline bool is_registered() const { return this->_registered; }
    inline bool has_unregistered_descendants() const { return this->_unregistered_descendants; }
    inline bool has_descendants_with_unregistered_components() const {
        return this->_unregistered_descendants_components;
    }
    inline DynamicArrayIterator<Entity *> *get_children_iterator() {
        return new DynamicArrayIterator<Entity *>(this->_children);
    }
    inline DynamicArrayIterator<Component *> *get_components_iterator() {
        return new DynamicArrayIterator<Component *>(this->_components);
    }
    inline void set_removal_callback(std::function<void(Entity *)> removal_callback) {
        this->_removal_callback = removal_callback;
    }
    inline void call_removal_callback() { this->_removal_callback(this); }
    void set_registered(bool ready);
    void set_unregistered_descendants(bool unregistered_descendants);
    bool components_are_registered();
    void set_unregistered_descendants_components(bool unregistered_descendants_components);
    void set_active(bool is_active);
    void set_auto_managed(bool auto_managed);
    void reparent(Entity *parent);
    void add_child(Entity *entity);
    void register_all_descendants(DynamicArray<Entity *> *entities, std::function<void(Entity *)> removal_callback);
    void register_all_descendants_components(DynamicArray<Component *> *components,
                                             std::function<void(Component *)> removal_callback);
    void register_all_components(DynamicArray<Component *> *components,
                                 std::function<void(Component *)> removal_callback);
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
    bool _registered;
    bool _unregistered_descendants;
    bool _unregistered_descendants_components;
    Entity *_parent;
    DynamicArray<Entity *> *_children;
    DynamicArray<Component *> *_components;
    std::function<void(Entity *)> _removal_callback;
};
