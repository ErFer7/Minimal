#pragma once

#include "managed_component.h"

class Graphics2DComponent : public ManagedComponent {
   public:
    Graphics2DComponent(std::string name = "") : ManagedComponent(true, name) {}
    ~Graphics2DComponent() override = default;

   protected:
    void register_component() override;
    void unregister_component() override;
};
