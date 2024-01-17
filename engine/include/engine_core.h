#pragma once

#include "./containers/entity_container.h"
#include "./managers/behaviour_manager.h"
#include "./managers/graphics_manager.h"
#include "./managers/main_behaviour_manager.h"
#include "./managers/physics_manager.h"
#include "raylib.h"

// Forward declarations to lower dependencies in the hierarchy
class EntityContainer;
class MainBehaviourManager;
class BehaviourManager;
class PhysicsManager;
class GraphicsManager;

/**
 * @class EngineCore
 * @brief The core engine class responsible for managing various subsystems.
 */
class EngineCore {
   public:
    /**
     * @brief Construct a new EngineCore object.
     * @param screen_width The width of the screen.
     * @param screen_height The height of the screen.
     * @param title The title of the window.
     * @param target_fps The target FPS of the game.
     * @param resizable Whether the window is resizable.
     * @param fullscreen Whether the window is fullscreen.
     * @param show_fps Whether to show the FPS counter.
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
     * @brief Get the entity container.
     * @return A pointer to the EntityContainer object.
     */
    EntityContainer *get_entity_container();

    /**
     * @brief Get the main behaviour manager.
     * @return A pointer to the MainBehaviourManager object.
     */
    MainBehaviourManager *get_main_behaviour_manager();

    /**
     * @brief Set the main behaviour manager.
     * @param main_behaviour_manager A pointer to the MainBehaviourManager object.
     */
    void set_main_behaviour_manager(MainBehaviourManager *main_behaviour_manager);

    /**
     * @brief Get the behaviour manager.
     * @return A pointer to the BehaviourManager object.
     */
    BehaviourManager *get_behaviour_manager();

    /**
     * @brief Get the physics manager.
     * @return A pointer to the PhysicsManager object.
     */
    PhysicsManager *get_physics_manager();

    /**
     * @brief Get the graphics manager.
     * @return A pointer to the GraphicsManager object.
     */
    GraphicsManager *get_graphics_manager();

    /**
     * @brief Initialize the main loop of the engine.
     */
    void init_main_loop();

   private:
    EntityContainer *_entity_container;
    MainBehaviourManager *_main_behaviour_manager;
    BehaviourManager *_behaviour_manager;
    PhysicsManager *_physics_manager;
    GraphicsManager *_graphics_manager;
};
