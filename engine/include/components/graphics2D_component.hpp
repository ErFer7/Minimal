#pragma once

#include "../types.hpp"
#include "component.hpp"
#include "raylib.h"
#include "transform2D_component.hpp"

enum class RenderingMode { SCREEN_SPACE, WORLD_SPACE_2D, WORLD_SPACE_3D };

class Graphics2DComponent : public Component {
    friend class Space;

   public:
    Graphics2DComponent(EngineCore *engine_core, Entity *entity);

    ~Graphics2DComponent() override;

    inline Texture2D get_texture() const { return this->_texture; }

    void set_texture(Texture2D texture);

    inline Color get_color() const { return this->_tint; }

    inline void set_color(Color color) { this->_tint = color; }

    inline RenderingMode get_rendering_mode() const { return this->_rendering_mode; }

    inline void set_rendering_mode(RenderingMode rendering_mode) { this->_rendering_mode = rendering_mode; }  // TODO: Fix this

    inline int get_layer() { return this->_layer; }

    inline void set_layer(int layer) { this->_layer = layer; }

    void draw();

   protected:
    void register_component() override;

    void unregister_component() override;

   private:
    inline Vector2 _get_position() { return this->_transform_component->get_position(); }

    void _update_destination_rectangle();

    void _update_origin();

   private:
    Texture2D _texture;
    Transform2DComponent *_transform_component;
    Rectangle _source_rectangle;
    Rectangle _destination_rectangle;
    Vector2 _origin;
    float _rotation;
    Color _tint;
    RenderingMode _rendering_mode;
    int _layer;
    Transform2DComponent::TransformUpdateListener _transform_update_listener;
};
