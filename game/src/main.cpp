#include "../../engine/include/engine_core.h"
#include "../../engine/include/entity.h"
#include "../../engine/include/entity_manager.h"

int main() {
    EngineCore *engine_core = new EngineCore();

    Entity *entity = new Entity("Test Entity");

    entity->add_child(new Entity("Test Entity"));

    engine_core->get_entity_manager()->add_entity(entity);

    engine_core->init_main_loop(1600, 800, "Sample");

    delete engine_core;

    return 0;
}
