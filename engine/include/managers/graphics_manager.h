#pragma once

#include "../components/graphics2D_component.h"
#include "component_manager.h"

class Graphics2DComponent;

class GraphicsManager : public ComponentManager {
   public:
    GraphicsManager(EngineCore *engine_core,
                    int screen_width,
                    int screen_height,
                    const char *title,
                    bool resizable = false,
                    bool fullscreen = false);
    ~GraphicsManager() = default;

    void init() override;
    void update() override;
    void exit() override;

   private:
    int _screen_width;
    int _screen_height;
    const char *_title;
    bool _resizable;
    bool _fullscreen;

    friend class Graphics2DComponent;
};