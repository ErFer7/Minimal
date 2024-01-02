#pragma once

#include "entity_container.h"
#include "raylib.h"

class MainManager {
   public:
    MainManager();
    ~MainManager();
    void init_main_window(int width, int height, const char *title);
    void init_main_loop();

   private:
    EntityContainer *_entity_container;
};
