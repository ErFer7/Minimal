#pragma once

#include <memory>
#include <vector>

#include "../components/component.hpp"
#include "../types.hpp"
#include "manager.hpp"

class ComponentManager : public Manager {
   public:
    ComponentManager() = default;
    ComponentManager(EngineCore *engine_core) : Manager(engine_core){};
    ComponentManager(const ComponentManager &other) noexcept { this->_copy(other); }
    ComponentManager(ComponentManager &&other) noexcept { this->_move(std::move(other)); }
    ~ComponentManager() override = default;

    ComponentManager &operator=(const ComponentManager &other) noexcept {
        this->_copy(other);

        return *this;
    }

    void update() override {};

   protected:
    virtual inline Component *register_component(Component component) {
        this->_components->push_back(component);
        return &this->_components->back();
    }

    virtual void unregister_component(Component *component);

   private:
    inline void _move(ComponentManager &&other) {
        this->_components.reset();
        this->_components = std::move(other._components);
    }

    void _copy(const ComponentManager &other) {
        this->_components.reset();
        this->_components = std::make_unique<std::vector<Component>>(*other._components);
    }

   private:
    std::unique_ptr<std::vector<Component>> _components;
};
