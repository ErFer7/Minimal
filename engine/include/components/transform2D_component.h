#pragma once

#include <functional>

#include "../entities/entity.h"
#include "../utils/dynamic_array.h"
#include "component.h"
#include "raymath.h"

class Transform2DComponent : public Component {
   public:
    Transform2DComponent(std::string name = "");
    ~Transform2DComponent() override;

    inline Vector2 get_local_position() const { return this->_local_position; }
    inline float get_local_rotation() const { return this->_local_rotation; }
    inline Vector2 get_local_scale() const { return this->_local_scale; }
    inline Vector2 get_world_position() { return this->_world_position; }
    inline float get_world_rotation() { return this->_world_rotation; }
    inline Vector2 get_world_scale() { return this->_world_scale; }
    inline void add_update_callback(std::function<void(Transform2DComponent *)> *callback) {
        this->_update_callbacks->add(callback);
    }
    inline void remove_update_callback(std::function<void(Transform2DComponent *)> *callback) {
        this->_update_callbacks->remove(callback);
    }
    void on_entity_parent_added(Entity *parent) override;
    void on_entity_parent_removed(Entity *parent) override;
    void on_add_to_entity() override;
    void on_remove_from_entity() override;
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

   private:
    Vector2 _local_position;
    float _local_rotation;
    Vector2 _local_scale;
    Vector2 _world_position;
    float _world_rotation;
    Vector2 _world_scale;
    Vector2 _origin_position;
    float _origin_rotation;
    Vector2 _origin_scale;
    std::function<void(Transform2DComponent *)> *_update_origin_callback;
    DynamicArray<std::function<void(Transform2DComponent *)> *> *_update_callbacks;

    void _update_origin(Transform2DComponent *parent_transform);
    void _update_world_position();
    void _update_world_rotation();
    void _update_world_scale();
    void _notify_update();
    void _on_parent_transform_updated(Transform2DComponent *parent_transform);
};