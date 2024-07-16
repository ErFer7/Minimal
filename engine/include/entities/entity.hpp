#pragma once

#include <memory>
#include <typeinfo>
#include <utility>
#include <vector>

#include "../types.hpp"
#include "../utils/engine_core_dependency_injector.h"
#include "../utils/event.hpp"

class Entity : public EngineCoreDependencyInjector {
    friend class EntityContainer;

   public:
    typedef std::vector<std::unique_ptr<Entity>> ChildrenVector;
    typedef std::vector<std::unique_ptr<Component>> ComponentsVector;

   public:
    Entity() = default;
    Entity(const Entity &) = delete;
    Entity(EngineCore *engine_core, Entity *parent);
    ~Entity();

    Entity &operator=(const Entity &) = delete;  // Prevent assignment. The entity should not be copied.

    inline const bool is_active() const { return this->_ancestor_active && this->_active; }
    void set_active(bool is_active);

    inline Entity *get_parent() const { return this->_parent; }
    void set_parent(Entity *parent);

    template <typename T = Entity, typename... Args>
    void create_child(Args &&...args) {
        this->_register_created_child(this->create_unique<T>(this, std::forward<Args>(args)...));
    }

    bool has_child(Entity *entity) const;
    inline Entity *get_child(unsigned int index) const { return this->_children->at(index).get(); }
    unsigned int get_child_index(Entity *entity) const;
    inline unsigned int get_child_count() const { return this->_children->size(); }
    void destroy_child(unsigned int index);
    void destroy_all_children();

    void destroy();

    template <typename T = Component, typename... Args>
    void create_component(Args &&...args) {
        this->_register_created_component(this->create_unique<T>(std::forward<Args>(args)...));
    }

    bool has_component(const std::type_info &type_info) const;
    Component *get_component(unsigned int index) const;
    Component *get_component(const std::type_info &type_info) const;
    unsigned int get_component_index(Component *component) const;
    unsigned int get_component_index(const std::type_info &type_info) const;
    void destroy_component(unsigned int index);
    void destroy_component(const std::type_info &type_info);
    void destroy_all_components();

    template <typename T>
    inline bool has_component() const {
        return this->has_component(typeid(T));
    }

    template <typename T>
    inline T *get_component() const {
        return static_cast<T *>(this->get_component(typeid(T)));
    }

    template <typename T>
    inline unsigned int get_component_index() const {
        return this->get_component_index(typeid(T));
    }

    template <typename T>
    inline void remove_component() {
        this->destroy_component(typeid(T));
    }

   private:
    inline const bool _is_ancestor_active() const { return this->_ancestor_active; }
    void _set_ancestor_active(bool parent_active);
    void _register_created_child(std::unique_ptr<Entity> child);
    void _register_created_component(std::unique_ptr<Component> component);

   private:
    bool _active;
    bool _ancestor_active;
    Entity *_parent;
    std::unique_ptr<ChildrenVector> _children;
    std::unique_ptr<ComponentsVector> _components;
    Event<Entity *> _on_destroy;
    Event<Entity *, Entity *> _on_parent_change;
    Event<Entity *> _on_child_create;
    Event<Entity *> _on_child_destroy;
    Event<Entity *> _on_child_add;
    Event<Entity *> _on_child_remove;
    Event<Entity *, Component *> _on_component_create;
    Event<Entity *, Component *> _on_component_destroy;
};
