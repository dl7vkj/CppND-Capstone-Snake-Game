#ifndef RENDERER_H
#define RENDERER_H

#include <unordered_map>
#include <vector>
#include <string>
#include <algorithm>

#include "SDL.h"

// #include "player.h"
// #include "entity.h"
#include "sdl_texture.h"
// #include "render_component.h"
// #include "star.h"

#include "game_object.h"

class Renderer {
public:
    // Render() = delete;
    explicit Renderer(const std::size_t screen_width,
                      const std::size_t screen_height);
    ~Renderer();

    void Render();

    // void InitBgStars();
    // void RenderBgStars();

    void UpdateWindowTitle(int health, int score, int life, int fps);

    SDL_Renderer &GetSDLRendererHandle() { return *sdl_renderer; }


    // Note: Return as pointer, so caller can check if nullptr returned
    SDLTexture *GetTexture(std::string filename) {
        // TODO: Return nullptr if we can not load the texture
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

    // void RegisterTextureComponent(RenderComponent *texture_component) {
    //     if (nullptr == texture_component)
    //         return;
    //     textureComponents_.push_back(texture_component);
    // }

    // void UnregisterTextureComponent(RenderComponent *texture_component) {
    //     textureComponents_.erase(
    //         std::remove_if(textureComponents_.begin(), textureComponents_.end(),
    //         [&](auto const &x){ return x == texture_component; }),
    //         textureComponents_.end());
    // }

    void RegisterGameObjects(GameObject *game_object) {
        if (nullptr == game_object)
            return;
        gameObjects_.push_back(game_object);
    }

    void UnregisterGameObjects(GameObject *game_object) {
        gameObjects_.erase(
            std::remove_if(gameObjects_.begin(), gameObjects_.end(),
            [&](auto const &x){ return x == game_object; }),
            gameObjects_.end());
    }

    std::size_t GetScreenWidth() const { return screenWidth_; }
    std::size_t GetScreenHeight() const { return screenHeight_; }

private:
    SDL_Window *sdl_window;
    SDL_Renderer *sdl_renderer;
    std::unordered_map<std::string, std::unique_ptr<SDLTexture>> textures_;
    std::vector<GameObject*> gameObjects_;
    // std::vector<RenderComponent*> textureComponents_;
    // std::vector<std::unique_ptr<Star>> bgStars_;

    const std::size_t screenWidth_;
    const std::size_t screenHeight_;
};

#endif