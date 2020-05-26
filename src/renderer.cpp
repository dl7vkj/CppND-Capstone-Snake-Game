#include "renderer.h"

#include <iostream>
#include <string>
#include <sstream>
#include <random>

#include "SDL_image.h"

#include "utility.h"
#include "graphics_component.h"


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
