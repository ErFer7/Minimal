#pragma once

#include "../engine_core.h"
#include "managed_component.h"
#include "raylib.h"

class Graphics2DComponent : public ManagedComponent {
   public:
    Graphics2DComponent(EngineCore *engine_core, std::string name = "");
    ~Graphics2DComponent() override;

    inline Texture2D *get_texture() { return this->_texture; }
    void set_texture(Texture2D texture);
    void on_add_to_entity() override;
    void on_remove_from_entity() override;
    void on_entity_parent_added(Entity *parent) override;
    void on_entity_parent_removed(Entity *parent) override;
    void draw();

   protected:
    void register_component() override;
    void unregister_component() override;

   private:
    Texture2D *_texture;
    Vector2 _position;
    float _rotation;
    Vector2 _scale;
    Vector2 _offset_position;
    float _offset_rotation;
    Vector2 _offset_scale;
    Rectangle _source_rectangle;
    Rectangle _destination_rectangle;
    Color _tint;
};
