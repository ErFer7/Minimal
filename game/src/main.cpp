#include "../../engine/include/engine_core.h"

int main() {
    EngineCore *engine_core = new EngineCore();

    engine_core->init_main_loop(1600, 800, "Sample");

    delete engine_core;

    return 0;
}
