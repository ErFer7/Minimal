#pragma once

#include "./containers/entity_container.h"
#include "./managers/behaviour_manager.h"
#include "./managers/main_behaviour_manager.h"
#include "./managers/physics_manager.h"
#include "raylib.h"

// Forward declarations to lower dependencies in the hierarchy
class EntityContainer;
class MainBehaviourManager;
class BehaviourManager;
class PhysicsManager;

class EngineCore {
   public:
    EngineCore();
    ~EngineCore();
    EntityContainer *get_entity_manager();
    MainBehaviourManager *get_main_behaviour_manager();
    void set_main_behaviour_manager(MainBehaviourManager *main_behaviour_manager);
    BehaviourManager *get_behaviour_manager();
    PhysicsManager *get_physics_manager();
    void init_main_loop(int window_width, int window_height, const char *window_title);

   private:
    EntityContainer *_entity_manager;
    MainBehaviourManager *_main_behaviour_manager;
    BehaviourManager *_behaviour_manager;
    PhysicsManager *_physics_manager;
};
