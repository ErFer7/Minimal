#pragma once

#include "./components/behaviour_component.h"
#include "./components/component.h"
#include "./components/graphics2D_component.h"
#include "./components/managed_component.h"
#include "./components/physics_component.h"
#include "./components/transform2D_component.h"
#include "./containers/entity_container.h"
#include "./engine_core.h"
#include "./entities/entity.h"
#include "./entities/entity2D.h"
#include "./managers/behaviour_manager.h"
#include "./managers/component_manager.h"
#include "./managers/graphics_manager.h"
#include "./managers/main_behaviour_manager.h"
#include "./managers/manager.h"
#include "./managers/physics_manager.h"
#include "./utils/dynamic_array.h"
#include "raylib.h"
#include "raymath.h"

/**
 * @brief The MinimalEngine class is responsible for executing the main loop of the minimal engine.
 *
 * It provides a static template function `execute` that takes a type `T` as a template parameter,
 * which must be a subclass of `MainBehaviourManager`. The `execute` function initializes the engine core,
 * creates an instance of `T`, sets it as the main behaviour manager, and starts the main loop.
 *
 * @note The `execute` function assumes ownership of the engine core and deletes it when the main loop ends.
 */
class MinimalEngine {
   public:
    /**
     * Executes the engine with the specified parameters.
     *
     * @param screen_width The width of the screen.
     * @param screen_height The height of the screen.
     * @param title The title of the window.
     * @param target_fps The target frames per second (default is 60).
     * @param resizable Whether the window is resizable or not (default is false).
     * @param fullscreen Whether the window is fullscreen or not (default is false).
     * @param show_fps Whether to show the frames per second on the window (default is false).
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

        _engine_core = new EngineCore(screen_width, screen_height, title, target_fps, resizable, fullscreen, show_fps);
        T *main_behaviour_manager = new T(_engine_core);

        _engine_core->set_main_behaviour_manager(main_behaviour_manager);
        _engine_core->init_main_loop();

        if (_engine_core != nullptr) {
            delete _engine_core;
            _engine_core = nullptr;
        }
    }

   private:
    static EngineCore *_engine_core;
};
