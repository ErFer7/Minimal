#include "../../include/containers/resource_container.h"

ResourceContainer::ResourceContainer() {
    this->_shaders = new std::unordered_map<std::string, Shader>();
    this->_data = new std::unordered_map<std::string, unsigned char *>();
    this->_images = new std::unordered_map<std::string, Image>();
    this->_fonts = new std::unordered_map<std::string, Font>();
    this->_models = new std::unordered_map<std::string, Model>();
}

ResourceContainer::~ResourceContainer() {
    if (this->_shaders != nullptr) {
        this->unload_all_shaders();
        delete this->_shaders;
        this->_shaders = nullptr;
    }

    if (this->_data != nullptr) {
        this->unload_all_data();
        delete this->_data;
        this->_data = nullptr;
    }

    if (this->_texts != nullptr) {
        this->unload_all_texts();
        delete this->_texts;
        this->_texts = nullptr;
    }

    if (this->_images != nullptr) {
        this->unload_all_images();
        delete this->_images;
        this->_images = nullptr;
    }

    if (this->_textures != nullptr) {
        this->unload_all_textures();
        delete this->_textures;
        this->_textures = nullptr;
    }

    if (this->_fonts != nullptr) {
        this->unload_all_fonts();
        delete this->_fonts;
        this->_fonts = nullptr;
    }

    if (this->_models != nullptr) {
        this->unload_all_models();
        delete this->_models;
        this->_models = nullptr;
    }
}

Shader ResourceContainer::load_cached_shader(std::string name, bool reload) {
    if (reload || this->_shaders->find(name) == this->_shaders->end()) {
        Shader shader = LoadShader(name.append(".vs").c_str(), name.append(".fs").c_str());
        (*this->_shaders)[name] = shader;
    }

    return (*this->_shaders)[name];
}

void ResourceContainer::unload_cached_shader(std::string name) {
    UnloadShader(this->_shaders->at(name));
    this->_shaders->erase(name);
}

unsigned char *ResourceContainer::load_cached_data(std::string name, bool reload) {
    if (reload || this->_data->find(name) == this->_data->end()) {
        unsigned char *data = LoadFileData(name.c_str(), nullptr);
        (*this->_data)[name] = data;
    }

    return (*this->_data)[name];
}

void ResourceContainer::unload_cached_data(std::string name) {
    UnloadFileData(this->_data->at(name));
    this->_data->erase(name);
}

char *ResourceContainer::load_cached_text(std::string name, bool reload) {
    if (reload || this->_texts->find(name) == this->_texts->end()) {
        char *text = LoadFileText(name.c_str());
        (*this->_texts)[name] = text;
    }

    return (*this->_texts)[name];
}

void ResourceContainer::unload_cached_text(std::string name) {
    UnloadFileText(this->_texts->at(name));
    this->_texts->erase(name);
}

Image ResourceContainer::load_cached_image(std::string name, ImageArgs args, bool reload) {
    if (reload || this->_images->find(name) == this->_images->end()) {
        Image image;

        switch (args.mode) {
            case ImageLoadingMode::DEFAULT:
                image = LoadImage(name.c_str());
                break;
            case ImageLoadingMode::RAW:
                image = LoadImageRaw(name.c_str(),
                                     args.rawArgs.width,
                                     args.rawArgs.height,
                                     args.rawArgs.format,
                                     args.rawArgs.headerSize);
                break;
            case ImageLoadingMode::SVG:
                image = LoadImageSvg(name.c_str(), args.svgArgs.width, args.svgArgs.height);
                break;
            case ImageLoadingMode::ANIM:
                image = LoadImageAnim(name.c_str(), args.animArgs.frames);
                break;
        }

        (*this->_images)[name] = image;
    }

    return (*this->_images)[name];
}

void ResourceContainer::unload_cached_image(std::string name) {
    UnloadImage(this->_images->at(name));
    this->_images->erase(name);
}

Texture2D ResourceContainer::load_cached_texture(std::string name, bool reload) {
    if (reload || this->_textures->find(name) == this->_textures->end()) {
        Texture2D texture = LoadTexture(name.c_str());
        (*this->_textures)[name] = texture;
    }

    return (*this->_textures)[name];
}

void ResourceContainer::unload_cached_texture(std::string name) {
    UnloadTexture(this->_textures->at(name));
    this->_textures->erase(name);
}

Font ResourceContainer::load_cached_font(std::string name, FontArgs args, bool reload) {
    if (reload || this->_fonts->find(name) == this->_fonts->end()) {
        Font font;

        switch (args.mode) {
            case FontLoadingMode::DEFAULT:
                font = LoadFont(name.c_str());
                break;
            case FontLoadingMode::EXTENDED:
                font = LoadFontEx(name.c_str(),
                                  args.extendedArgs.fontSize,
                                  args.extendedArgs.codepoints,
                                  args.extendedArgs.codepointCount);
                break;
        }

        (*this->_fonts)[name] = font;
    }

    return (*this->_fonts)[name];
}

void ResourceContainer::unload_cached_font(std::string name) {
    UnloadFont(this->_fonts->at(name));
    this->_fonts->erase(name);
}

Model ResourceContainer::load_cached_model(std::string name, bool reload) {
    if (reload || this->_models->find(name) == this->_models->end()) {
        Model model = LoadModel(name.c_str());
        (*this->_models)[name] = model;
    }

    return (*this->_models)[name];
}

void ResourceContainer::unload_cached_model(std::string name) {
    UnloadModel(this->_models->at(name));
    this->_models->erase(name);
}

void ResourceContainer::unload_all_shaders() {
    for (auto &shader : *this->_shaders) {
        UnloadShader(shader.second);
    }

    this->_shaders->clear();
}

void ResourceContainer::unload_all_data() {
    for (auto &data : *this->_data) {
        UnloadFileData(data.second);
    }

    this->_data->clear();
}

void ResourceContainer::unload_all_texts() {
    for (auto &text : *this->_texts) {
        UnloadFileText(text.second);
    }

    this->_texts->clear();
}

void ResourceContainer::unload_all_images() {
    for (auto &image : *this->_images) {
        UnloadImage(image.second);
    }

    this->_images->clear();
}

void ResourceContainer::unload_all_textures() {
    for (auto &texture : *this->_textures) {
        UnloadTexture(texture.second);
    }

    this->_textures->clear();
}

void ResourceContainer::unload_all_fonts() {
    for (auto &font : *this->_fonts) {
        UnloadFont(font.second);
    }

    this->_fonts->clear();
}

void ResourceContainer::unload_all_models() {
    for (auto &model : *this->_models) {
        UnloadModel(model.second);
    }

    this->_models->clear();
}
