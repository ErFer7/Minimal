#pragma once

#include <memory>
#include <utility>

class EngineCore;

/**
 * A class that provides dependency injection for objects that depend on the EngineCore.
 */
class EngineCoreDependencyInjector {
   public:
    EngineCoreDependencyInjector() = default;

    /**
     * Constructs an EngineCoreDependentInjector object.
     *
     * engine_core: A pointer to the EngineCore object.
     */
    EngineCoreDependencyInjector(EngineCore *engine_core) : _engine_core_ref(engine_core){};

    virtual ~EngineCoreDependencyInjector() = default;

    /**
     * Retrieves the EngineCore object associated with this injector.
     */
    inline EngineCore *get_engine_core() const { return this->_engine_core_ref; }

    template <typename T, typename... Args>
    T create(Args &&...args) {
        return T(this->_engine_core_ref, std::forward<Args>(args)...);
    }

    /**
     * Creates an instance of type T with the given arguments.
     *
     * T: The type of object to create.
     * Args: The types of the arguments to pass to the constructor of T.
     * args? The arguments to pass to the constructor of T.
     */
    template <typename T, typename... Args>
    T *create_heap_allocated(Args &&...args) {
        return new T(this->_engine_core_ref, std::forward<Args>(args)...);
    }

    template <typename T, typename... Args>
    std::unique_ptr<T> create_unique(Args &&...args) {
        return std::make_unique<T>(this->_engine_core_ref, std::forward<Args>(args)...);
    }

   private:
    EngineCore *_engine_core_ref;
};