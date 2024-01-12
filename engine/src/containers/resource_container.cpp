#include "../../include/containers/resource_container.h"

ResourceContainer::ResourceContainer() {
    this->_shaders = std::unordered_map<std::string, Shader>();
    this->_data = std::unordered_map<std::string, unsigned char>();
    this->_images = std::unordered_map<std::string, Image>();
    this->_fonts = std::unordered_map<std::string, Font>();
    this->_models = std::unordered_map<std::string, Model>();
}

ResourceContainer::~ResourceContainer() {}

Shader *ResourceContainer::get_shader_ref(std::string name) {
    if (this->_shaders.find(name) == this->_shaders.end()) {
        Shader shader = LoadShader(name.append(".vs").c_str(), name.append(".fs").c_str());

        if (shader.id != 0U) {
            this->_shaders[name] = shader;
        } else {
            return nullptr;
        }
    }

    return &this->_shaders[name];
}
