#pragma once

class EngineCore;

/**
 * @class EngineCoreDependentInjector
 * @brief A class that provides dependency injection for objects that depend on the EngineCore.
 */
class EngineCoreDependentInjector {
   public:
    /**
     * @brief Constructs an EngineCoreDependentInjector object.
     *
     * @param engine_core A pointer to the EngineCore object.
     */
    EngineCoreDependentInjector(EngineCore *engine_core) : _engine_core_ref(engine_core){};

    ~EngineCoreDependentInjector() = default;

    /**
     * @brief Retrieves the EngineCore object associated with this injector.
     *
     * @return A pointer to the EngineCore object.
     */
    inline EngineCore *get_engine_core() { return this->_engine_core_ref; }

    /**
     * @brief Creates an instance of type T with the given arguments.
     *
     * @tparam T The type of object to create.
     * @tparam Args The types of the arguments to pass to the constructor of T.
     * @param args The arguments to pass to the constructor of T.
     * @return A pointer to the created instance of type T.
     */
    template <typename T, typename... Args>
    T *create(Args &&...args) {
        return new T(this->_engine_core_ref, std::forward<Args>(args)...);
    }

   private:
    EngineCore *_engine_core_ref;
};