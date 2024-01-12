#include "../../include/components/component.h"

Component::Component(EngineCore *engine_core, bool unique, std::string name)
    : EngineCoreDependentInjector(engine_core) {
    this->_name = name;
    this->_active = true;
    this->_unique = unique;
}
