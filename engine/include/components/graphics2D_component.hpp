#pragma once

#include <functional>

#include "../types.hpp"
#include "../utils/transform_system2D.hpp"
#include "component.hpp"
#include "raylib.h"

enum class RenderingMode { SCREEN_SPACE, WORLD_SPACE_2D, WORLD_SPACE_3D };

class Graphics2DComponent : public Component {
   public:
    Graphics2DComponent(EngineCore *engine_core, Entity *entity);
    ~Graphics2DComponent() override;

    inline Texture2D *get_texture() { return this->_texture; }
    inline Color get_color() { return this->_tint; }
    inline void set_color(Color color) { this->_tint = color; }
    inline RenderingMode get_rendering_mode() { return this->_rendering_mode; }
    inline void set_rendering_mode(RenderingMode rendering_mode) { this->_rendering_mode = rendering_mode; }
    inline Vector2 get_position() { return this->_transform_system->get_result_position(); }
    inline int get_layer() { return this->_layer; }
    inline void set_layer(int layer) { this->_layer = layer; }
    void set_texture(Texture2D texture);
    void on_entity_parent_added(Entity *parent);
    void on_entity_parent_removed(Entity *parent);
    void draw();

   protected:
    Component *register_component() override;
    void unregister_component() override;

   private:
    Texture2D *_texture;
    TransformSystem2D *_transform_system;
    Rectangle _source_rectangle;
    Rectangle _destination_rectangle;
    Vector2 _origin;
    Color _tint;
    RenderingMode _rendering_mode;
    int _layer;
    std::function<void(Transform2DComponent *)> *_update_transform_callback;

    void _on_transform_updated(Transform2DComponent *transform);
    void _update_destination_rectangle();
    void _update_origin();
};
