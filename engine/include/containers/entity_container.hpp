#pragma once

#include <memory>
#include <utility>

#include "../types.hpp"
#include "../utils/engine_core_dependency_injector.hpp"

class EntityContainer : public EngineCoreDependencyInjector {
   public:
    EntityContainer() = default;
    EntityContainer(EntityContainer &&other) noexcept : _root(std::move(other._root)) {}
    EntityContainer(EngineCore *engine_core);
    ~EntityContainer();

    EntityContainer &operator=(EntityContainer &&other) noexcept {
        if (this != &other) {
            this->_root = std::move(other._root);
        }

        return *this;
    }

    template <typename T = Entity, typename... Args>
    T *create_entity(Args &&...args) {
        return static_cast<T *>(this->_register_created_entity(this->create_unique<T>(this->_root.get(), std::forward<Args>(args)...)));
    }

    void destroy_all_entities();

   private:
    Entity *_register_created_entity(std::unique_ptr<Entity> entity);

   private:
    std::unique_ptr<Entity> _root;
};
