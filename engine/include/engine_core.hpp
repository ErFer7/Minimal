#pragma once

#include <memory>

#include "./containers/entity_container.hpp"
#include "./managers/behaviour_manager.hpp"
#include "./managers/graphics_manager.hpp"
#include "./managers/main_behaviour_manager.hpp"
#include "types.hpp"

/**
 * The core engine class responsible for managing various subsystems.
 */
class EngineCore {
   public:
    EngineCore() = default;

    /**
     * Construct a new EngineCore object.
     *
     * screen_width: The width of the screen.
     * screen_height: The height of the screen.
     * title: The title of the window.
     * target_fps: The target FPS of the game.
     * resizable: Whether the window is resizable.
     * fullscreen: Whether the window is fullscreen.
     * show_fps: Whether to show the FPS counter.
     */
    EngineCore(int screen_width,
               int screen_height,
               const char *title,
               int target_fps = 60,
               bool resizable = false,
               bool fullscreen = false,
               bool show_fps = false);

    ~EngineCore();

    /**
     * Get the entity container.
     */
    inline EntityContainer *get_entity_container() { return this->_entity_container.get(); };

    /**
     * Get the main behaviour manager.
     */
    inline MainBehaviourManager *get_main_behaviour_manager() { return this->_main_behaviour_manager.get(); };

    /**
     * Get the behaviour manager.
     */
    inline BehaviourManager *get_behaviour_manager() { return this->_behaviour_manager.get(); };

    /**
     * Get the graphics manager.
     */
    inline GraphicsManager *get_graphics_manager() { return this->_graphics_manager.get(); };

    template <typename T = MainBehaviourManager>
    void create_main_behaviour_manager() {
        this->_main_behaviour_manager = std::make_unique<T>(this);
    }

    /**
     * Initialize the main loop of the engine.
     */
    void init_main_loop();

   private:
    std::unique_ptr<EntityContainer> _entity_container;
    std::unique_ptr<MainBehaviourManager> _main_behaviour_manager;
    std::unique_ptr<BehaviourManager> _behaviour_manager;
    std::unique_ptr<GraphicsManager> _graphics_manager;
};
