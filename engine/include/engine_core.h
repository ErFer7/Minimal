#pragma once

#include "entity.h"
#include "entity_manager.h"
#include "raylib.h"

class EngineCore {
   public:
    EngineCore();
    ~EngineCore();
    void init_main_loop(int window_width, int window_height, const char *window_title);

   private:
    EntityManager *_entity_manager;
};
