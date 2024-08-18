#pragma once

#include <memory>
#include <typeinfo>
#include <utility>
#include <vector>

#include "../types.hpp"
#include "../utils/engine_core_dependency_injector.hpp"
#include "../utils/event.hpp"

// TODO: Implement an activity state
// TODO: Implement name with a hash map
// TODO: Implement has_child for instance, type and name

class Entity : public EngineCoreDependencyInjector {
    friend class EntityContainer;

   public:
    typedef std::vector<Entity> ChildrenVector;
    typedef std::vector<Component *> ComponentsVector;

   public:
    Entity() = default;
    Entity(EngineCore *engine_core, Entity *parent);
    Entity(const Entity &other);
    Entity(Entity &&other) noexcept;
    ~Entity();

    Entity &operator=(const Entity &other) noexcept {
        this->_copy(other);

        return *this;
    }

    inline Entity *get_parent() const { return this->_parent; }

    template <typename T = Entity, typename... Args>
    T *create_child(Args &&...args) {
        this->_children->push_back(this->create<T>(this, std::forward<Args>(args)...));

        T *child = &this->_children->back();
        this->_on_child_create(child);

        return child;
    }

    inline Entity *get_child(unsigned int index) const { return &this->_children->at(index); }
    const unsigned int get_child_index(Entity *entity) const;
    inline const unsigned int get_child_count() const { return this->_children->size(); }
    void destroy_child(unsigned int index);
    void destroy_all_children();

    void destroy();

    template <typename T = Component, typename... Args>
    T *create_component(Args &&...args) {
        return static_cast<T *>(this->_register_created_component(this->create<T>(std::forward<Args>(args)...)));
    }

    bool has_component(const std::type_info &type_info) const;
    Component *get_component(unsigned int index) const;
    Component *get_component(const std::type_info &type_info) const;
    const unsigned int get_component_index(Component *component) const;
    const unsigned int get_component_index(const std::type_info &type_info) const;
    inline const unsigned int get_component_count() const { return this->_components->size(); }
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
    Component *_register_created_component(Component component);
    void _move(Entity &&other);
    void _copy(const Entity &other);

   private:
    Entity *_parent;
    std::unique_ptr<ChildrenVector> _children;
    std::unique_ptr<ComponentsVector> _components;
    Event<Entity *> _on_destroy;
    Event<Entity *> _on_child_create;
    Event<Entity *> _on_child_destroy;
    Event<Entity *, Component *> _on_component_create;
    Event<Entity *, Component *> _on_component_destroy;
};
