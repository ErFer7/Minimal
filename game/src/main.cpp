#include "../../engine/include/engine_core.h"
#include "../../engine/include/entity.h"
#include "../../engine/include/entity_manager.h"
#include "../include/main_behaviour_manager.h"

int main() {
    EngineCore *engine_core = new EngineCore();
    MainBehaviourManager *main_behaviour_manager = new MainBehaviourManager(engine_core);

    engine_core->set_main_behaviour_manager(main_behaviour_manager);
    engine_core->init_main_loop(1600, 800, "Sample");

    delete engine_core;

    return 0;
}
