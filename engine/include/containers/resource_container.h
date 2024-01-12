#pragma once

#include <string>
#include <unordered_map>

#include "../utils/dynamic_array.h"
#include "raylib.h"

class ResourceContainer {
   public:
    ResourceContainer();
    ~ResourceContainer();

    inline void unload_shader(Shader shader) { UnloadShader(shader); }
    inline Shader get_shader_instance(std::string name) {
        return LoadShader(name.append(".vs").c_str(), name.append(".fs").c_str());
    }
    Shader *get_shader_ref(std::string name);

   private:
    std::unordered_map<std::string, Shader> _shaders;      // VRAM
    std::unordered_map<std::string, unsigned char> _data;  // RAM
    std::unordered_map<std::string, Image> _images;        // RAM
    std::unordered_map<std::string, Font> _fonts;          // VRAM
    std::unordered_map<std::string, Model> _models;
};