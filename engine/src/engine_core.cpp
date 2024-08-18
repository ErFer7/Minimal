#include "../include/engine_core.hpp"

#include "raylib.h"

EngineCore::EngineCore(int screen_width,
                       int screen_height,
                       const char *title,
                       int target_fps,
                       bool resizable,
                       bool fullscreen,
                       bool show_fps) {
    this->_entity_container = EntityContainer(this);
    this->_behaviour_manager = BehaviourManager(this);
    this->_graphics_manager = GraphicsManager(this, screen_width, screen_height, title, target_fps, resizable, fullscreen, show_fps);
}

void EngineCore::init_main_loop() {
    this->_behaviour_manager.init();
    this->_graphics_manager.init();
    this->_main_behaviour_manager.init();

    while (!WindowShouldClose()) {
        this->_main_behaviour_manager.update();
        this->_behaviour_manager.update();
        this->_graphics_manager.update();
    }

    this->_main_behaviour_manager.exit();
    this->_graphics_manager.exit();
    this->_behaviour_manager.exit();
}
