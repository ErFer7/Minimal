#include "../include/main_manager.h"

MainManager::MainManager() { this->_entity_container = new EntityContainer(); }

MainManager::~MainManager() { delete this->_entity_container; }

void MainManager::init_main_window(int width, int height, const char *title) { InitWindow(width, height, title); }

void MainManager::init_main_loop() {
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);
        EndDrawing();
    }
}
