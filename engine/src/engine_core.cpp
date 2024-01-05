#include "../include/engine_core.h"

EngineCore::EngineCore() { this->_entity_manager = new EntityManager(); }

EngineCore::~EngineCore() { delete this->_entity_manager; }

void EngineCore::init_main_loop(int window_width, int window_height, const char *window_title) {
    InitWindow(window_width, window_height, window_title);

    while (!WindowShouldClose()) {
        this->_entity_manager->update();

        BeginDrawing();
        ClearBackground(BLACK);
        EndDrawing();
    }

    CloseWindow();

    if (this->_entity_manager != nullptr) {
        delete this->_entity_manager;
        this->_entity_manager = nullptr;
    }
}
