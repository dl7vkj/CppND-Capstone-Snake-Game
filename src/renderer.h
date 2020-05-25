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
    void UpdateWindowTitle(int health, int score, int life, int fps);

    SDLTexture *GetTexture(std::string filename) {
        auto result = textures_.find(filename);
        if (result != textures_.end()) {
            // Texture already exists
            SDL_LogMessage(SDL_LOG_CATEGORY_RENDER, SDL_LOG_PRIORITY_DEBUG,
                       "Texture found %s", filename.c_str());
            return result->second.get();
        } else {
            // Create texture
            SDL_LogMessage(SDL_LOG_CATEGORY_RENDER, SDL_LOG_PRIORITY_DEBUG,
                       "Load texture %s", filename.c_str());
            textures_.emplace(filename, std::make_unique<SDLTexture>(filename,
                *sdl_renderer));
            return textures_[filename].get();

        }
    }

    void RegisterTextureComponent(TextureComponent *texture_component) {
        if (nullptr == texture_component)
            return;
        textureComponents_.push_back(texture_component);
    }

    void UnregisterTextureComponent(TextureComponent *texture_component) {
        textureComponents_.erase(
            std::remove_if(textureComponents_.begin(), textureComponents_.end(),
            [&](auto const &x){ return x == texture_component; }),
            textureComponents_.end());
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