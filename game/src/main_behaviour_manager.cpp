#include "../include/main_behaviour_manager.h"

MainBehaviourManager::MainBehaviourManager(EngineCore *engine_core) {
    this->_engine_core = engine_core;
}

MainBehaviourManager::~MainBehaviourManager() {}

void MainBehaviourManager::init() {
    this->_engine_core->get_entity_manager()->add_entity(new Entity("Sample"));
}

void MainBehaviourManager::update() {}

void MainBehaviourManager::exit() {}
