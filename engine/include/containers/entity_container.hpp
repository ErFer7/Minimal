#pragma once

#include <memory>

#include "../types.hpp"
#include "../utils/engine_core_dependency_injector.h"

class EntityContainer : public EngineCoreDependencyInjector {
   public:
    EntityContainer() = default;
    EntityContainer(EngineCore *engine_core);
    ~EntityContainer();

    template <typename T = Entity, typename... Args>
    void create_entity(Args &&...args) {
        this->_register_created_entity(this->create_unique<T>(this->_root.get(), std::forward<Args>(args)...));
    }

    void destroy_entity(Entity *entity);

    void destroy_all_entities();

   private:
    void _register_created_entity(std::unique_ptr<Entity> entity);

   private:
    std::unique_ptr<Entity> _root;
};
