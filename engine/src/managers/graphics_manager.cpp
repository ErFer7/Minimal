#include "../../include/managers/graphics_manager.h"

bool is_layer_null(Layer layer) { return layer.layer < 0; }

GraphicsManager::GraphicsManager(EngineCore *engine_core,
                                 int screen_width,
                                 int screen_height,
                                 const char *title,
                                 int target_fps,
                                 bool resizable,
                                 bool fullscreen,
                                 bool show_fps)
    : ComponentManager(engine_core) {
    this->_screen_width = screen_width;
    this->_screen_height = screen_height;
    this->_title = title;
    this->_resizable = resizable;
    this->_fullscreen = fullscreen;
    this->_show_fps = show_fps;
    this->_target_fps = target_fps;
    this->_camera2D = {0};
    this->_camera2D.target = (Vector2){0.0f, 0.0f};
    this->_camera2D.offset = (Vector2){0.0f, 0.0f};
    this->_camera2D.rotation = 0.0f;
    this->_camera2D.zoom = 1.0f;
    this->_screen_space = Space{true, new DynamicArray<Layer>(4, Layer{-1}, is_layer_null)};
    this->_world2D_space = Space{true, new DynamicArray<Layer>(4, Layer{-1}, is_layer_null)};
    this->_screen_space_layers_sorting_mode = new std::unordered_map<int, SortingMode>();
    this->_world2D_space_layers_sorting_mode = new std::unordered_map<int, SortingMode>();
}

GraphicsManager::~GraphicsManager() {
    if (this->_screen_space._layers != nullptr) {
        this->_clear_layer_array(this->_screen_space._layers);
        delete this->_screen_space._layers;
        this->_screen_space._layers = nullptr;
    }

    if (this->_world2D_space._layers != nullptr) {
        this->_clear_layer_array(this->_world2D_space._layers);
        delete this->_world2D_space._layers;
        this->_world2D_space._layers = nullptr;
    }

    if (this->_screen_space_layers_sorting_mode != nullptr) {
        delete this->_screen_space_layers_sorting_mode;
        this->_screen_space_layers_sorting_mode = nullptr;
    }

    if (this->_world2D_space_layers_sorting_mode != nullptr) {
        delete this->_world2D_space_layers_sorting_mode;
        this->_world2D_space_layers_sorting_mode = nullptr;
    }
}

void GraphicsManager::init() {
    InitWindow(this->_screen_width, this->_screen_height, this->_title);

    if (this->_resizable) {
        SetWindowState(FLAG_WINDOW_RESIZABLE);
    }

    if (this->_fullscreen) {
        ToggleFullscreen();
    }

    SetTargetFPS(this->_target_fps);

    this->_camera2D.offset = {(float)this->_screen_width / 2.0f, (float)this->_screen_height / 2.0f};
}

void GraphicsManager::update() {
    if (IsWindowResized()) {
        this->_screen_width = GetScreenWidth();
        this->_screen_height = GetScreenHeight();
        this->_camera2D.offset = {(float)this->_screen_width / 2.0f, (float)this->_screen_height / 2.0f};
    }

    if (this->_world2D_space.dirty) {
        this->_world2D_space.dirty = false;
        this->_sort_layer_array(this->_world2D_space._layers);
    }

    if (this->_screen_space.dirty) {
        this->_screen_space.dirty = false;
        this->_sort_layer_array(this->_screen_space._layers);
    }

    this->_optimize_layer_array(this->_world2D_space._layers);
    this->_optimize_layer_array(this->_screen_space._layers);

    BeginDrawing();
    ClearBackground(BLACK);

    BeginMode2D(this->_camera2D);
    this->_draw_layer_array(this->_world2D_space._layers);
    EndMode2D();

    this->_draw_layer_array(this->_screen_space._layers);

    if (this->_show_fps) {
        DrawFPS(GetScreenWidth() - 95, 10);
    }

    EndDrawing();
}

void GraphicsManager::exit() { CloseWindow(); }

void GraphicsManager::set_layer_sorting_mode(int layer, SortingMode sorting_mode, RenderingMode rendering_mode) {
    if (rendering_mode == RenderingMode::WORLD_SPACE_2D) {
        (*this->_world2D_space_layers_sorting_mode)[layer] = sorting_mode;
        this->_world2D_space.dirty = true;
    } else if (rendering_mode == RenderingMode::SCREEN_SPACE) {
        (*this->_screen_space_layers_sorting_mode)[layer] = sorting_mode;
        this->_screen_space.dirty = true;
    }
}

SortingMode GraphicsManager::get_layer_sorting_mode(int layer, RenderingMode rendering_mode) {
    if (rendering_mode == RenderingMode::WORLD_SPACE_2D) {
        if (this->_world2D_space_layers_sorting_mode->find(layer) != this->_world2D_space_layers_sorting_mode->end()) {
            return (*this->_world2D_space_layers_sorting_mode)[layer];
        }
    } else if (rendering_mode == RenderingMode::SCREEN_SPACE) {
        if (this->_screen_space_layers_sorting_mode->find(layer) != this->_screen_space_layers_sorting_mode->end()) {
            return (*this->_screen_space_layers_sorting_mode)[layer];
        }
    }

    return SortingMode::NONE;
}

void GraphicsManager::register_component(Component *component) {
    Graphics2DComponent *graphics2D_component = static_cast<Graphics2DComponent *>(component);

    RenderingMode rendering_mode = graphics2D_component->get_rendering_mode();
    int component_layer = graphics2D_component->get_layer();

    if (rendering_mode == RenderingMode::WORLD_SPACE_2D) {
        bool layer_exists = false;

        for (unsigned int i = 0; i < this->_world2D_space._layers->get_size(); i++) {
            Layer layer = this->_world2D_space._layers->nullable_at(i);

            if (!is_layer_null(layer) && layer.layer == component_layer) {
                layer.components->add(graphics2D_component);
                layer.dirty = true;
                layer_exists = true;
                break;
            }
        }

        if (!layer_exists) {
            Layer layer = Layer{component_layer,
                                true,
                                this->get_layer_sorting_mode(component_layer, rendering_mode),
                                new DynamicArray<Graphics2DComponent *>(16)};

            layer.components->add(graphics2D_component);
            this->_world2D_space._layers->add(layer);
        }
    } else if (rendering_mode == RenderingMode::SCREEN_SPACE) {
        bool layer_exists = false;

        for (unsigned int i = 0; i < this->_screen_space._layers->get_size(); i++) {
            Layer layer = this->_screen_space._layers->nullable_at(i);

            if (!is_layer_null(layer) && layer.layer == graphics2D_component->get_layer()) {
                layer.components->add(graphics2D_component);
                layer.dirty = true;
                layer_exists = true;
                break;
            }
        }

        if (!layer_exists) {
            Layer layer = Layer{component_layer,
                                true,
                                this->get_layer_sorting_mode(component_layer, rendering_mode),
                                new DynamicArray<Graphics2DComponent *>(16)};

            layer.components->add(graphics2D_component);
            this->_screen_space._layers->add(layer);
        }
    }
}

void GraphicsManager::unregister_component(Component *component) {
    Graphics2DComponent *graphics2D_component = static_cast<Graphics2DComponent *>(component);

    RenderingMode rendering_mode = graphics2D_component->get_rendering_mode();
    int component_layer = graphics2D_component->get_layer();

    if (rendering_mode == RenderingMode::WORLD_SPACE_2D) {
        for (unsigned int i = 0; i < this->_world2D_space._layers->get_size(); i++) {
            Layer layer = this->_world2D_space._layers->nullable_at(i);

            if (!is_layer_null(layer) && layer.layer == component_layer) {
                layer.components->remove(graphics2D_component, false);
                layer.dirty = true;
                break;
            }
        }
    } else if (rendering_mode == RenderingMode::SCREEN_SPACE) {
        for (unsigned int i = 0; i < this->_screen_space._layers->get_size(); i++) {
            Layer layer = this->_screen_space._layers->nullable_at(i);

            if (!is_layer_null(layer) && layer.layer == component_layer) {
                layer.components->remove(graphics2D_component, false);
                layer.dirty = true;
                break;
            }
        }
    }
}

void GraphicsManager::_update_layer(Graphics2DComponent *graphics2D_component, Layer *old_layer) {}

void GraphicsManager::_sort_layer_array(DynamicArray<Layer> *array) {
    // TODO: Limit the sort to visible layers only

    array->sort([](Layer layer_a, Layer layer_b) -> bool {
        if (is_layer_null(layer_a)) {
            return true;
        } else if (is_layer_null(layer_a)) {
            return false;
        }

        return layer_a.layer < layer_b.layer;
    });

    for (unsigned int i = 0; i < array->get_size(); i++) {
        Layer layer = array->nullable_at(i);

        if (!is_layer_null(layer) && layer.dirty) {
            layer.dirty = false;

            if (layer.sorting_type == SortingMode::TOP_TO_DOWN) {
                layer.components->sort([](Graphics2DComponent *comp_a, Graphics2DComponent *comp_b) -> bool {
                    if (comp_a == nullptr) {
                        return true;
                    } else if (comp_b == nullptr) {
                        return false;
                    }

                    return comp_a->get_position().y < comp_b->get_position().y;
                });
            } else if (layer.sorting_type == SortingMode::ISOMETRIC) {
                layer.components->sort([](Graphics2DComponent *comp_a, Graphics2DComponent *comp_b) -> bool {
                    if (comp_a == nullptr) {
                        return true;
                    } else if (comp_b == nullptr) {
                        return false;
                    }

                    return (comp_a->get_position().x + comp_a->get_position().y) <
                           (comp_b->get_position().x + comp_b->get_position().y);
                });
            }
        }
    }
}

void GraphicsManager::_draw_layer_array(DynamicArray<Layer> *array) {
    for (unsigned int i = 0; i < array->get_size(); i++) {
        Layer layer = array->nullable_at(i);

        if (!is_layer_null(layer)) {
            for (unsigned int j = 0; j < layer.components->get_size(); j++) {
                Graphics2DComponent *graphics2D_component = layer.components->nullable_at(j);

                if (graphics2D_component != nullptr && graphics2D_component->is_active()) {
                    graphics2D_component->draw();
                }
            }
        }
    }
}

void GraphicsManager::_optimize_layer_array(DynamicArray<Layer> *array) {
    for (unsigned int i = 0; i < array->get_size(); i++) {
        Layer layer = array->nullable_at(i);

        if (!is_layer_null(layer)) {
            if (layer.components->get_element_count() > 0) {
                layer.components->optimize();
            } else {
                delete layer.components;
                layer.components = nullptr;

                array->nullable_remove_at(i, false);
            }
        }
    }

    array->optimize();
}

void GraphicsManager::_clear_layer_array(DynamicArray<Layer> *array) {
    for (unsigned int i = 0; i < array->get_size(); i++) {
        Layer layer = array->nullable_at(i);

        if (!is_layer_null(layer)) {
            delete layer.components;
            layer.components = nullptr;

            array->nullable_remove_at(i, false);
        }
    }

    array->clear();
}
