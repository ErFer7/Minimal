#pragma once

class IComponent {
   public:
    virtual ~IComponent() = default;
    virtual void update() = 0;
};