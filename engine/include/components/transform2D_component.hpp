#pragma once

#include "../types.hpp"
#include "../utils/event.hpp"
#include "../utils/transform_system2D.hpp"
#include "component.hpp"

class Transform2DComponent : public Component {
   public:
    Transform2DComponent(EngineCore *engine_core, Entity *entity);
    ~Transform2DComponent() override;

    inline Vector2 get_local_position() const { return this->_transform_system.get_offset_position(); }
    inline float get_local_rotation() const { return this->_transform_system.get_offset_rotation(); }
    inline Vector2 get_local_scale() const { return this->_transform_system.get_offset_scale(); }
    inline Vector2 get_world_position() { return this->_transform_system.get_result_position(); }
    inline float get_world_rotation() { return this->_transform_system.get_result_rotation(); }
    inline Vector2 get_world_scale() { return this->_transform_system.get_result_scale(); }
    inline Transform2D get_local_transform() { return this->_transform_system.get_offset(); }
    inline Transform2D get_world_transform() { return this->_transform_system.get_result(); }
    void set_local_position(Vector2 position);
    void set_local_rotation(float rotation);
    void set_local_scale(Vector2 scale);
    void set_local_scale(float scale);
    void set_world_position(Vector2 position);
    void set_world_rotation(float rotation);
    void set_world_scale(Vector2 scale);
    void set_world_scale(float scale);
    void translate(Vector2 translation);
    void rotate(float rotation);
    void scale(Vector2 scale);
    void scale(float scale);

   protected:
    Component *register_component() override;
    void unregister_component() override;

   private:
    void _on_parent_transform_updated_callback(Transform2DComponent *parent_transform);

   private:
    TransformSystem2D _transform_system;
    Event<Transform2DComponent *> _on_update;
};