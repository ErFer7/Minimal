#pragma once

class Entity {
   public:
    Entity();
    Entity(bool auto_managed);
    ~Entity();
    unsigned int inline get_id() { return this->_id; }
    void inline set_active(bool is_active) { this->_is_active = is_active; }
    bool inline is_active() { return this->_is_active; }
    void inline set_auto_managed(bool auto_managed) { this->_auto_managed = auto_managed; }
    bool inline is_auto_managed() { return this->_auto_managed; }

   private:
    unsigned int _id;
    bool _is_active;
    bool _auto_managed;

    static unsigned int _next_id;
};