#pragma once

#include <utility>

#include "../entities/entity.hpp"
#include "../types.hpp"
#include "../utils/engine_core_dependency_injector.hpp"

class EntityContainer : public EngineCoreDependencyInjector {
   public:
    EntityContainer() = default;
    EntityContainer(EngineCore *engine_core);
    ~EntityContainer();

    template <typename T = Entity, typename... Args>
    T *create_entity(Args &&...args) {
        return static_cast<T *>(this->_root.create_child(std::forward<Args>(args)...));
    }

    void destroy_all_entities();

   private:
    Entity _root;
};
