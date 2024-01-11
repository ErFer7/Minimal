#include "../../include/managers/graphics_manager.h"

GraphicsManager::GraphicsManager(EngineCore *engine_core,
                                 int screen_width,
                                 int screen_height,
                                 const char *title,
                                 bool resizable,
                                 bool fullscreen)
    : ComponentManager(engine_core) {
    this->_screen_width = screen_width;
    this->_screen_height = screen_height;
    this->_title = title;
    this->_resizable = resizable;
    this->_fullscreen = fullscreen;
}

void GraphicsManager::init() {
    InitWindow(this->_screen_width, this->_screen_height, this->_title);

    if (this->_resizable) {
        SetWindowState(FLAG_WINDOW_RESIZABLE);
    }

    if (this->_fullscreen) {
        ToggleFullscreen();
    }
}

void GraphicsManager::update() {
    DynamicArray<Component *> *components = this->get_components();

    BeginDrawing();
    ClearBackground(BLACK);

    for (unsigned int i = 0; i < components->get_size(); i++) {
        Graphics2DComponent *graphics2D_component = static_cast<Graphics2DComponent *>(components->nullable_at(i));

        if (graphics2D_component != nullptr && graphics2D_component->is_active()) {
            // TODO: Implement
        }
    }

    EndDrawing();
}

void GraphicsManager::exit() { CloseWindow(); }
