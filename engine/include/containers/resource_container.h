#pragma once

#include <string>
#include <unordered_map>

#include "../utils/dynamic_array.hpp"
#include "raylib.h"

enum class ImageLoadingMode { DEFAULT, RAW, SVG, ANIM };
enum class FontLoadingMode { DEFAULT, EXTENDED };

struct DefaultImageArgs {};

struct RawImageArgs {
    int width;
    int height;
    int format;
    int headerSize;
};

struct SvgImageArgs {
    int width;
    int height;
};

struct AnimImageArgs {
    int *frames;
};

struct DefaultFontArgs {};

struct ExtendedFontArgs {
    int fontSize;
    int *codepoints;
    int codepointCount;
};

struct ImageArgs {
    ImageLoadingMode mode;

    union {
        DefaultImageArgs defaultArgs;
        RawImageArgs rawArgs;
        SvgImageArgs svgArgs;
        AnimImageArgs animArgs;
    };
};

struct FontArgs {
    FontLoadingMode mode;

    union {
        DefaultFontArgs defaultArgs;
        ExtendedFontArgs extendedArgs;
    };
};

class ResourceContainer {
   public:
    ResourceContainer();
    ~ResourceContainer();

    Shader load_cached_shader(std::string name, bool reload = false);
    void unload_cached_shader(std::string name);
    unsigned char *load_cached_data(std::string name, bool reload = false);
    void unload_cached_data(std::string name);
    char *load_cached_text(std::string name, bool reload = false);
    void unload_cached_text(std::string name);
    Image load_cached_image(std::string name, ImageArgs args = {ImageLoadingMode::DEFAULT}, bool reload = false);
    void unload_cached_image(std::string name);
    Texture2D load_cached_texture(std::string name, bool reload = false);
    void unload_cached_texture(std::string name);
    Font load_cached_font(std::string name, FontArgs args = {FontLoadingMode::DEFAULT}, bool reload = false);
    void unload_cached_font(std::string name);
    Model load_cached_model(std::string name, bool reload = false);
    void unload_cached_model(std::string name);
    void unload_all_shaders();
    void unload_all_data();
    void unload_all_texts();
    void unload_all_images();
    void unload_all_textures();
    void unload_all_fonts();
    void unload_all_models();

   private:
    std::unordered_map<std::string, Shader> *_shaders;                   // VRAM
    std::unordered_map<std::string, unsigned char *> *_data;             // RAM
    std::unordered_map<std::string, char *> *_texts;                     // RAM
    std::unordered_map<std::string, Image> *_images;                     // RAM
    std::unordered_map<std::string, Texture2D> *_textures;               // VRAM
    std::unordered_map<std::string, Font> *_fonts;                       // VRAM
    std::unordered_map<std::string, Model> *_models;                     // RAM
    std::unordered_map<std::string, Material> *_materials;               // RAM

    // TODO: Implement these
    std::unordered_map<std::string, ModelAnimation> *_model_animations;  // RAM
    std::unordered_map<std::string, Wave> *_waves;                       // RAM
    std::unordered_map<std::string, Sound> *_sounds;                     // RAM
    std::unordered_map<std::string, Music> *_musics;                     // RAM
    std::unordered_map<std::string, AudioStream> *_audio_streams;        // RAM
};