#pragma once

#include <unordered_map>

#include "../types.hpp"
#include "component_manager.hpp"
#include "raylib.h"

class Graphics2DComponent;
enum class RenderingMode;

enum class SortingMode { NONE, TOP_TO_DOWN, ISOMETRIC };

struct Layer {
    int layer;
    bool dirty;
    SortingMode sorting_type;
    DynamicArray<Graphics2DComponent *> *components;
};

bool is_layer_null(Layer layer);

struct Space {
    bool dirty;
    DynamicArray<Layer> *_layers;
};

class GraphicsManager : public ComponentManager {
   public:
    GraphicsManager() = default;
    GraphicsManager(EngineCore *engine_core,
                    int screen_width,
                    int screen_height,
                    const char *title,
                    int target_fps = 60,
                    bool resizable = false,
                    bool fullscreen = false,
                    bool show_fps = false);
    ~GraphicsManager() override;

    void init() override;
    void update() override;
    void exit() override;
    void set_layer_sorting_mode(int layer, SortingMode sorting_mode, RenderingMode rendering_mode);
    SortingMode get_layer_sorting_mode(int layer, RenderingMode rendering_mode);

   protected:
    void register_component(Component *component) override;
    void unregister_component(Component *component) override;

   private:
    int _screen_width;
    int _screen_height;
    const char *_title;
    bool _resizable;
    bool _fullscreen;
    bool _show_fps;
    int _target_fps;
    Camera2D _camera2D;
    Space _screen_space;
    Space _world2D_space;
    std::unordered_map<int, SortingMode> *_screen_space_layers_sorting_mode;
    std::unordered_map<int, SortingMode> *_world2D_space_layers_sorting_mode;

    void _update_layer(Graphics2DComponent *graphics2D_component, Layer *old_layer);
    void _sort_layer_array(DynamicArray<Layer> *array);
    void _draw_layer_array(DynamicArray<Layer> *array);
    void _optimize_layer_array(DynamicArray<Layer> *array);
    void _clear_layer_array(DynamicArray<Layer> *array);

    friend class Graphics2DComponent;
};