#include "../../engine/include/main_manager.h"

int main() {
    MainManager *mainManager = new MainManager();

    mainManager->init_main_window(800, 450, "Sample");
    mainManager->init_main_loop();

    return 0;
}
