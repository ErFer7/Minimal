#pragma once

#include "./containers/entity_container.h"
#include "./managers/behaviour_manager.h"
#include "./managers/graphics_manager.h"
#include "./managers/main_behaviour_manager.h"
#include "./managers/physics_manager.h"

// Forward declarations to lower dependencies in the hierarchy
class EntityContainer;
class MainBehaviourManager;
class BehaviourManager;
class PhysicsManager;
class GraphicsManager;

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

    ~EngineCore() = default;

    /**
     * Get the entity container.
     */
    const EntityContainer *get_entity_container() const;

    /**
     * Get the main behaviour manager.
     */
    const MainBehaviourManager *get_main_behaviour_manager() const;

    /**
     * Get the behaviour manager.
     */
    const BehaviourManager *get_behaviour_manager() const;

    /**
     * Get the physics manager.
     */
    const PhysicsManager *get_physics_manager() const;

    /**
     * Get the graphics manager.
     */
    const GraphicsManager *get_graphics_manager() const;

    template <typename T = MainBehaviourManager>
    void create_main_behaviour_manager() {
        this->_main_behaviour_manager = T(this);
    }

    /**
     * Initialize the main loop of the engine.
     */
    void init_main_loop();

   private:
    EntityContainer _entity_container;
    MainBehaviourManager _main_behaviour_manager;
    BehaviourManager _behaviour_manager;
    PhysicsManager _physics_manager;
    GraphicsManager _graphics_manager;
};
