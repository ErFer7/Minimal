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

class EngineCore {
   public:
    EngineCore(int screen_width, int screen_height, const char *title, bool resizable = false, bool fullscreen = false);
    ~EngineCore();
    EntityContainer *get_entity_manager();
    MainBehaviourManager *get_main_behaviour_manager();
    void set_main_behaviour_manager(MainBehaviourManager *main_behaviour_manager);
    BehaviourManager *get_behaviour_manager();
    PhysicsManager *get_physics_manager();
    GraphicsManager *get_graphics_manager();
    void init_main_loop();

   private:
    EntityContainer *_entity_manager;
    MainBehaviourManager *_main_behaviour_manager;
    BehaviourManager *_behaviour_manager;
    PhysicsManager *_physics_manager;
    GraphicsManager *_graphics_manager;
};
