#include "../../include/components/component.h"

Component::Component(bool unique, std::string name) {
    this->_name = name;
    this->_active = true;
    this->_unique = unique;
}
