#include "../include/engine_core.h"

EngineCore::EngineCore() {
    this->_entity_manager = new EntityContainer(this);
    this->_main_behaviour_manager = nullptr;
    this->_behaviour_manager = new BehaviourManager(this);
}

EngineCore::~EngineCore() {
    if (this->_entity_manager != nullptr) {
        delete this->_entity_manager;
        this->_entity_manager = nullptr;
    }

    if (this->_main_behaviour_manager != nullptr) {
        delete this->_main_behaviour_manager;
        this->_main_behaviour_manager = nullptr;
    }

    if (this->_behaviour_manager != nullptr) {
        delete this->_behaviour_manager;
        this->_behaviour_manager = nullptr;
    }
}

EntityContainer *EngineCore::get_entity_manager() {
    return this->_entity_manager;
}

MainBehaviourManager *EngineCore::get_main_behaviour_manager() {
    return this->_main_behaviour_manager;
}

void EngineCore::set_main_behaviour_manager(MainBehaviourManager *main_behaviour_manager) {
    this->_main_behaviour_manager = main_behaviour_manager;
}

BehaviourManager *EngineCore::get_behaviour_manager() {
    return this->_behaviour_manager;
}

void EngineCore::init_main_loop(int window_width, int window_height, const char *window_title) {
    this->_behaviour_manager->init();
    this->_main_behaviour_manager->init();

    InitWindow(window_width, window_height, window_title);

    while (!WindowShouldClose()) {
        this->_main_behaviour_manager->update();
        this->_behaviour_manager->update();

        BeginDrawing();
        ClearBackground(BLACK);
        EndDrawing();
    }

    CloseWindow();

    this->_main_behaviour_manager->exit();
    this->_behaviour_manager->exit();
}
