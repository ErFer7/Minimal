#pragma once

#include "manager_interface.h"

class BehaviourManager : public IManager {
   public:
    BehaviourManager();
    ~BehaviourManager() override;
    void init() override;
    void update() override;
    void exit() override;
};
