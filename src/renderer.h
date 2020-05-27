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

    std::size_t GetScreenWidth() const;
    std::size_t GetScreenHeight() const;
    SDL_Renderer *GetSDLRendererHandle();
    Texture *GetTextureHandle(std::string filename);

    void RegisterGameObjects(GameObject *game_object);
    void UnregisterGameObjects(GameObject *game_object);

    void Render();
    void UpdateWindowTitle(int health, int score, int life, int fps);

private:
    SDL_Window *sdl_window{nullptr};
    SDL_Renderer *sdl_renderer{nullptr};
    std::unordered_map<std::string, std::unique_ptr<Texture>> textures_{};
    std::vector<GameObject*> gameObjects_{};

    const std::size_t screenWidth_;
    const std::size_t screenHeight_;
};

#endif
