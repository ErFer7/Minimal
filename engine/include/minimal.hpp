#pragma once

#include "./components/behaviour_component.hpp"
#include "./components/component.hpp"
#include "./components/graphics2D_component.hpp"
#include "./components/transform2D_component.hpp"
#include "./containers/entity_container.hpp"
#include "./engine_core.hpp"
#include "./entities/entity.hpp"
#include "./entities/entity2D.hpp"
#include "./managers/behaviour_manager.hpp"
#include "./managers/component_manager.hpp"
#include "./managers/graphics_manager.hpp"
#include "./managers/main_behaviour_manager.hpp"
#include "./managers/manager.hpp"
#include "raylib.h"
#include "raymath.h"
#include "types.hpp"

class MinimalEngine {
   public:
    template <typename T>
    static void execute(int screen_width,
                        int screen_height,
                        const char *title,
                        int target_fps = 60,
                        bool resizable = false,
                        bool fullscreen = false,
                        bool show_fps = false) {
        static_assert(std::is_base_of<MainBehaviourManager, T>::value, "T must be a type of MainBehaviourManager");

        EngineCore engine_core = EngineCore(screen_width, screen_height, title, target_fps, resizable, fullscreen, show_fps);

        engine_core.create_main_behaviour_manager<T>();
        engine_core.init_main_loop();
    }
};
