#include "renderer.h"

#include <iostream>
#include <string>
#include <sstream>
#include <random>

#include "SDL_image.h"

#include "utility.h"
#include "component.h"


// RUBRIC: Class constructors utilize member initialization lists.
Renderer::Renderer(const std::size_t screen_width,
                   const std::size_t screen_height)
    : screenWidth_(screen_width),
      screenHeight_(screen_height)
{
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize.\n";
        std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
    }

    // Create Window
    sdl_window = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED,
                                  SDL_WINDOWPOS_CENTERED, screenWidth_,
                                  screenHeight_, SDL_WINDOW_SHOWN);

    if (nullptr == sdl_window) {
        std::cerr << "Window could not be created.\n";
        std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
    }

    // Create renderer
    sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
    if (nullptr == sdl_renderer) {
        std::cerr << "Renderer could not be created.\n";
        std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
    }

    IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
}

Renderer::~Renderer() {
    SDL_DestroyWindow(sdl_window);
    IMG_Quit();
    SDL_Quit();
}

std::size_t Renderer::GetScreenWidth() const { return screenWidth_; }

std::size_t Renderer::GetScreenHeight() const { return screenHeight_; }

SDL_Renderer *Renderer::GetSDLRendererHandle() { return sdl_renderer; }

// Note: Return as pointer, so caller can check if nullptr returned
Texture *Renderer::GetTextureHandle(std::string filename) {
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
            sdl_renderer));
        return textures_[filename].get();
    }
}

void Renderer::RegisterGameObjects(GameObject *game_object) {
    if (nullptr == game_object)
        return;
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO,
                    "Register GameObject");
    gameObjects_.push_back(game_object);
}

void Renderer::UnregisterGameObjects(GameObject *game_object) {
    gameObjects_.erase(
        std::remove_if(gameObjects_.begin(), gameObjects_.end(),
        [&](auto const &x){ return x == game_object; }),
        gameObjects_.end());
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO,
                    "Unregister GameObject");
}

void Renderer::Render() {
    SDL_SetRenderDrawColor(sdl_renderer, 0x20, 0x20, 0x20, 0xFF);
    SDL_RenderClear(sdl_renderer);

    //Render graphics components
    for (auto &obj: gameObjects_) {
       obj->UpdateGraphics(*this);
    }

    SDL_RenderPresent(sdl_renderer);
}

// TODO: Add HUD
void Renderer::UpdateWindowTitle(int health, int score, int life, int fps)
{
    std::ostringstream stream;
    stream << "[ HEALTH " << health << " | SCORE " << score << " | LIVES " << life << " | FPS " << fps << " ]";
    // std::string title{"FPS: " + std::to_string(fps)};
    SDL_SetWindowTitle(sdl_window, stream.str().c_str());
}
