#pragma once

#include <functional>
#include <memory>
#include <unordered_map>

template <typename... Args>
class Event {
   public:
    typedef std::unordered_map<unsigned long, std::function<void(Args...)>> CallableMap;

   public:
    Event() : _next_id(0) { this->_callables = std::make_unique<CallableMap>(); }
    Event(const Event &other) { this->_copy(other); }
    Event(Event &&other) noexcept { this->_move(other); }
    ~Event() = default;

    inline Event &operator=(const Event &other) {
        this->_copy(other);

        return *this;
    }

    inline void operator()(Args... args) {
        for (auto &callable : *this->_callables) {
            callable(args...);
        }
    }

    inline unsigned long subscribe(std::function<void(Args...)> callable) {
        this->_callables->insert(std::make_pair(_next_id, callable));
        return _next_id++;
    }

    inline void unsubscribe(unsigned long callable_id) { _callables->erase(callable_id); }

   private:
    inline void _move(Event &&other) {
        if (this != &other) {
            this->_callables.reset();
            this->_callables = std::move(other._callables);
            this->_next_id = other._next_id;
        }
    }

    inline void _copy(const Event &other) {
        if (this != &other) {
            this->_callables.reset();
            this->_callables = std::make_unique<CallableMap>(*other._callables);
            this->_next_id = other._next_id;
        }
    }

   private:
    std::unique_ptr<CallableMap> _callables;
    unsigned long _next_id = 0;
};
