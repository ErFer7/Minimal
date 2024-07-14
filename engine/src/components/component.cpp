#include "../../include/components/component.h"

Component::Component(EngineCore *engine_core, bool unique) : EngineCoreDependencyInjector(engine_core) {
    this->_active = true;
    this->_unique = unique;
}
