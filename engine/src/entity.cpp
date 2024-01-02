#include "../include/entity.h"

unsigned int Entity::_next_id = 0;

Entity::Entity() {
    this->_id = _next_id++;
    this->_is_active = false;
    this->_auto_managed = true;
}

Entity::Entity(bool auto_managed) {
    this->_id = _next_id++;
    this->_is_active = false;
    this->_auto_managed = auto_managed;
}

Entity::~Entity() {}