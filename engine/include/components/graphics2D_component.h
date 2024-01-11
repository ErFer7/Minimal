#pragma once

#include "../engine_core.h"
#include "managed_component.h"
#include "raylib.h"

class Graphics2DComponent : public ManagedComponent {
   public:
    Graphics2DComponent(std::string name = "");
    ~Graphics2DComponent() override;

    inline Texture2D *get_texture() { return this->_texture; }
    inline void set_texture(Texture2D *texture) { this->_texture = texture; }
    void on_add_to_entity() override;
    void on_remove_from_entity() override;
    void on_entity_parent_added(Entity *parent) override;
    void on_entity_parent_removed(Entity *parent) override;

   protected:
    void register_component() override;
    void unregister_component() override;

   private:
    Texture2D *_texture;
};
