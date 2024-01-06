#pragma once

#include "behaviour_manager.h"
#include "entity.h"
#include "entity_manager.h"
#include "manager_interface.h"
#include "raylib.h"

class EngineCore {
   public:
    EngineCore();
    ~EngineCore();
    inline EntityManager *get_entity_manager() { return this->_entity_manager; }
    inline void set_main_behaviour_manager(IManager *main_behaviour_manager) {
        this->_main_behaviour_manager = main_behaviour_manager;
    }
    inline IManager *get_main_behaviour_manager() { return this->_main_behaviour_manager; }
    void init_main_loop(int window_width, int window_height, const char *window_title);

   private:
    EntityManager *_entity_manager;
    IManager *_main_behaviour_manager;
    BehaviourManager *_behaviour_manager;
};
