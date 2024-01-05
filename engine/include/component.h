#pragma once

class IComponent {
   public:
    IComponent() = default;
    virtual ~IComponent() = default;
    virtual void update() = 0;
};