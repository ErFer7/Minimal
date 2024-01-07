#pragma once

#include <functional>
#include <string>

class Component {
   public:
    Component(bool unique, std::string name = "");
    virtual ~Component() = default;
    inline std::string get_name() const { return this->_name; }
    inline void set_name(std::string name) { this->_name = name; }
    inline bool is_active() const { return this->_active; }
    inline void set_active(bool active) { this->_active = active; }
    inline bool is_unique() const { return this->_unique; }
    inline bool is_registered() const { return this->_registered; }
    inline void set_registered(bool registered) { this->_registered = registered; }
    inline void set_removal_callback(std::function<void(Component *)> removal_callback) {
        this->_removal_callback = removal_callback;
    }
    inline void call_removal_callback() { this->_removal_callback(this); }
    virtual void on_update() = 0;

   private:
    std::string _name;
    bool _active;
    bool _unique;
    bool _registered;
    std::function<void(Component *)> _removal_callback;
};
