#ifndef RENDERER_H
#define RENDERER_H

#include <unordered_map>
#include <vector>
#include <string>

#include "SDL.h"

#include "player.h"
#include "entity.h"
#include "sdl_texture.h"
#include "texture_component.h"

class Renderer {
public:
    // Render() = delete;
    explicit Renderer(const std::size_t screen_width,
                      const std::size_t screen_height);
    ~Renderer();
#if 0
  void Render(Player &player, std::list<Entity> &entities,
              std::list<Entity> &enemies);
#endif
    void Render();
    void UpdateWindowTitle(int fps);

    SDLTexture *GetTexture(std::string filename) {
        auto result = textures_.find(filename);
        if (result != textures_.end()) {
            // Texture already exists
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO,
                       "Texture found %s", filename.c_str());
            return result->second.get();
        } else {
            // Create texture
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO,
                       "Create texture %s", filename.c_str());
            textures_.emplace(filename, std::make_unique<SDLTexture>(filename,
                *sdl_renderer));
            return textures_[filename].get();

        }
    }

    void RegisterTextureComponent(TextureComponent *texture_component) {
        textureComponents_.push_back(texture_component);
    }

    void UnregisterTextureComponent(TextureComponent *texture_component) {
        if (nullptr == texture_component)
            return;
        auto result = std::find(textureComponents_.begin(),
            textureComponents_.end(), texture_component);
        if (result != textureComponents_.end()) {
            textureComponents_.erase(result);
        }
    }

    std::size_t GetScreenWidth() const { return screenWidth_; }
    std::size_t GetScreenHeight() const { return screenHeight_; }

private:
    SDL_Window *sdl_window;
    SDL_Renderer *sdl_renderer;
    std::unordered_map<std::string, std::unique_ptr<SDLTexture>> textures_;
    std::vector<TextureComponent*> textureComponents_;

    const std::size_t screenWidth_;
    const std::size_t screenHeight_;
};

#endif