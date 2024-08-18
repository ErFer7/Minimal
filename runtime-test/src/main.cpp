#include "../include/custom_main_behaviour_manager.hpp"

int main() {
    MinimalEngine::execute<CustomMainBehaviourManager>(1600, 800, "Sample", 75, false, false, true);

    return 0;
}
