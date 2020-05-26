#ifndef RENDERER_H
#define RENDERER_H

#include <unordered_map>
#include <vector>
#include <string>
#include <algorithm>

#include "SDL.h"

#include "texture.h"
#include "game_object.h"


class Renderer {
public:
    explicit Renderer(const std::size_t screen_width,
                      const std::size_t screen_height);
    ~Renderer();

    void Render();

    void UpdateWindowTitle(int health, int score, int life, int fps);

    SDL_Renderer &GetSDLRendererHandle() { return *sdl_renderer; }


    // Note: Return as pointer, so caller can check if nullptr returned
    Texture *GetTexture(std::string filename) {
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
            textures_.emplace(filename, std::make_unique<Texture>(filename,
                *sdl_renderer));
            return textures_[filename].get();

        }
    }

    void RegisterGameObjects(GameObject *game_object) {
        if (nullptr == game_object)
            return;
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO,
                       "Register GameObject");
        gameObjects_.push_back(game_object);
    }

    void UnregisterGameObjects(GameObject *game_object) {
        gameObjects_.erase(
            std::remove_if(gameObjects_.begin(), gameObjects_.end(),
            [&](auto const &x){ return x == game_object; }),
            gameObjects_.end());
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO,
                       "Unregister GameObject");
    }

    std::size_t GetScreenWidth() const { return screenWidth_; }
    std::size_t GetScreenHeight() const { return screenHeight_; }

private:
    SDL_Window *sdl_window;
    SDL_Renderer *sdl_renderer;
    std::unordered_map<std::string, std::unique_ptr<Texture>> textures_;
    std::vector<GameObject*> gameObjects_;

    const std::size_t screenWidth_;
    const std::size_t screenHeight_;
};

#endif