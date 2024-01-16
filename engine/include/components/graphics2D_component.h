#pragma once

#include <functional>

#include "../engine_core.h"
#include "managed_component.h"
#include "raylib.h"
#include "transform2D_component.h"

class Graphics2DComponent : public ManagedComponent {
   public:
    Graphics2DComponent(EngineCore *engine_core, std::string name = "");
    ~Graphics2DComponent() override;

    inline Texture2D *get_texture() { return this->_texture; }
    inline Color get_color() { return this->_tint; }
    inline void set_color(Color color) { this->_tint = color; }
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
    Vector2 _origin_position;
    float _origin_rotation;
    Vector2 _origin_scale;
    Vector2 _screen_position;
    float _screen_rotation;
    Vector2 _screen_scale;
    Vector2 _offset_position;
    float _offset_rotation;
    Vector2 _offset_scale;
    Rectangle _source_rectangle;
    Rectangle _destination_rectangle;
    Color _tint;
    std::function<void(Transform2DComponent *)> *_update_transform_callback;

    void _on_transform_updated(Transform2DComponent *transform);
};
