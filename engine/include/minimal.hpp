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

/**
 * The MinimalEngine class is responsible for executing the main loop of the minimal engine.
 *
 * It provides a static template function `execute` that takes a type `T` as a template parameter,
 * which must be a subclass of `MainBehaviourManager`. The `execute` function initializes the engine core,
 * creates an instance of `T`, sets it as the main behaviour manager, and starts the main loop.
 *
 * The `execute` function assumes ownership of the engine core and deletes it when the main loop ends.
 */
class MinimalEngine {
   public:
    /**
     * Executes the engine with the specified parameters.
     *
     * screen_width: The width of the screen.
     * screen_height: The height of the screen.
     * title: The title of the window.
     * target_fps: The target frames per second (default is 60).
     * resizable: Whether the window is resizable or not (default is false).
     * fullscreen: Whether the window is fullscreen or not (default is false).
     * show_fps: Whether to show the frames per second on the window (default is false).
     */
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
