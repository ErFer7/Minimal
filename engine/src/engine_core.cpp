#include "../include/engine_core.h"

EngineCore::EngineCore(int screen_width,
                       int screen_height,
                       const char *title,
                       bool resizable,
                       bool fullscreen) {
    this->_entity_manager = new EntityContainer(this);
    this->_main_behaviour_manager = nullptr;
    this->_behaviour_manager = new BehaviourManager(this);
    this->_physics_manager = new PhysicsManager(this);
    this->_graphics_manager = new GraphicsManager(this, screen_width, screen_height, title, resizable, fullscreen);
}

EngineCore::~EngineCore() {
    if (this->_entity_manager != nullptr) {
        delete this->_entity_manager;
        this->_entity_manager = nullptr;
    }

    if (this->_main_behaviour_manager != nullptr) {
        delete this->_main_behaviour_manager;
        this->_main_behaviour_manager = nullptr;
    }

    if (this->_behaviour_manager != nullptr) {
        delete this->_behaviour_manager;
        this->_behaviour_manager = nullptr;
    }

    if (this->_physics_manager != nullptr) {
        delete this->_physics_manager;
        this->_physics_manager = nullptr;
    }

    if (this->_graphics_manager != nullptr) {
        delete this->_graphics_manager;
        this->_graphics_manager = nullptr;
    }
}

// TODO: See if this can be inlined

EntityContainer *EngineCore::get_entity_manager() { return this->_entity_manager; }

MainBehaviourManager *EngineCore::get_main_behaviour_manager() { return this->_main_behaviour_manager; }

void EngineCore::set_main_behaviour_manager(MainBehaviourManager *main_behaviour_manager) {
    this->_main_behaviour_manager = main_behaviour_manager;
}

BehaviourManager *EngineCore::get_behaviour_manager() { return this->_behaviour_manager; }

PhysicsManager *EngineCore::get_physics_manager() { return this->_physics_manager; }

GraphicsManager *EngineCore::get_graphics_manager() { return this->_graphics_manager; }

void EngineCore::init_main_loop() {
    this->_behaviour_manager->init();
    this->_physics_manager->init();
    this->_graphics_manager->init();
    this->_main_behaviour_manager->init();

    while (!WindowShouldClose()) {
        this->_main_behaviour_manager->update();
        this->_behaviour_manager->update();
        this->_physics_manager->update();
        this->_graphics_manager->update();
    }

    this->_main_behaviour_manager->exit();
    this->_graphics_manager->exit();
    this->_physics_manager->exit();
    this->_behaviour_manager->exit();
}
