#pragma once

#include <memory>
#include <string>
#include <typeinfo>
#include <utility>
#include <vector>

#include "../components/component.h"
#include "../components/managed_component.h"
#include "../utils/engine_core_dependency_injector.h"

class EngineCore;

class Component;

class Entity : public EngineCoreDependencyInjector {
   public:
    typedef std::vector<std::unique_ptr<Entity>> ChildrenVector;
    typedef std::vector<Component *> ComponentsVector;

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
        this->_children->push_back(this->create_unique<T>(this, std::forward<Args>(args)...));
        Entity *entity = this->_children->back().get();

        entity->_set_ancestor_active(this->_ancestor_active && this->_active);
        entity->on_parent_add();
    }

    bool has_child(Entity *entity);
    unsigned int get_child_index(Entity *entity);
    void destroy_child(unsigned int index);
    void destroy_all_children();
    inline Entity *get_child(unsigned int index) { return this->_children->at(index).get(); }
    inline unsigned int get_child_count() const { return this->_children->size(); }

    bool has_descendant(Entity *entity);

    void destroy();

    void add_component(Component *component);
    bool has_component(const std::type_info &type_info);
    bool has_component(std::string component_name);
    void remove_component(unsigned int index);
    void remove_component(const std::type_info &type_info);
    void remove_component(std::string component_name);
    void remove_all_components();
    Component *get_component_at(unsigned int index);
    Component *get_component(const std::type_info &type_info);
    Component *get_component(std::string component_name);
    Component **get_all_components();
    Component **get_components_of_type(const std::type_info &type_info);

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
    inline const bool _is_ancestor_active() const { return this->_ancestor_active; }
    void _set_ancestor_active(bool parent_active);

   private:
    bool _active;
    bool _ancestor_active;
    Entity *_parent;
    std::unique_ptr<ChildrenVector> _children;
    std::unique_ptr<ComponentsVector> _components;
};
