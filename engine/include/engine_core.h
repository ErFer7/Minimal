#pragma once

#include "entity.h"
#include "entity_manager.h"
#include "raylib.h"

class EngineCore {
   public:
    EngineCore();
    ~EngineCore();
    inline EntityManager *get_entity_manager() { return this->_entity_manager; }
    void init_main_loop(int window_width, int window_height, const char *window_title);

   private:
    EntityManager *_entity_manager;
};
