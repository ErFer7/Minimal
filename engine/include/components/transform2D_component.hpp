#pragma once

#include "../types.hpp"
#include "../utils/event.hpp"
#include "../utils/transform_system2D.hpp"
#include "component.hpp"

class Transform2DComponent : public Component {
   public:
    typedef Event<Transform2DComponent *> TransformUpdateEvent;
    typedef TransformUpdateEvent::Listener TransformUpdateListener;

    Transform2DComponent(EngineCore *engine_core, Entity *entity);
    ~Transform2DComponent() override = default;

    inline Vector2 get_relative_position() const { return this->_transform_system.get_offset_position(); }
    inline float get_relative_rotation() const { return this->_transform_system.get_offset_rotation(); }
    inline Vector2 get_relative_scale() const { return this->_transform_system.get_offset_scale(); }
    inline Vector2 get_position() { return this->_transform_system.get_result_position(); }
    inline float get_rotation() { return this->_transform_system.get_result_rotation(); }
    inline Vector2 get_scale() { return this->_transform_system.get_result_scale(); }
    inline Transform2D get_relative_transform() { return this->_transform_system.get_offset(); }
    inline Transform2D get_transform() { return this->_transform_system.get_result(); }
    inline TransformUpdateEvent *get_on_update_event() { return &this->_on_update_event; }
    void set_relative_position(Vector2 position);
    void set_relative_rotation(float rotation);
    void set_relative_scale(Vector2 scale);
    void set_relative_scale(float scale);
    void set_position(Vector2 position);
    void set_rotation(float rotation);
    void set_scale(Vector2 scale);
    void set_scale(float scale);
    void translate(Vector2 translation);
    void rotate(float rotation);
    void scale(Vector2 scale);
    void scale(float scale);

   protected:
    Component *register_component() override;
    void unregister_component() override;

   private:
    TransformSystem2D _transform_system;
    TransformUpdateEvent _on_update_event;
    TransformUpdateListener _on_parent_transform_update_listener;
};