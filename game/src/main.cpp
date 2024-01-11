#include "../include/custom_main_behaviour_manager.h"

int main() {
    EngineCore *engine_core = new EngineCore(1600, 800, "Sample");
    CustomMainBehaviourManager *custom_main_behaviour_manager = new CustomMainBehaviourManager(engine_core);

    engine_core->set_main_behaviour_manager(custom_main_behaviour_manager);
    engine_core->init_main_loop();

    delete engine_core;

    return 0;
}
