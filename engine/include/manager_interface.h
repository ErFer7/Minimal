#pragma once

class IManager {
   public:
    virtual ~IManager() = default;
    virtual void init() = 0;
    virtual void update() = 0;
    virtual void exit() = 0;
};