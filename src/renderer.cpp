#include "renderer.h"
#include <iostream>
#include <string>

#include "SDL_image.h"

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
    for (auto texComp: textureComponents_) {
        texComp->Draw();
    }
    SDL_RenderPresent(sdl_renderer);
}

#if 0
void Renderer::Render(Player &player, std::list<Entity> &entities,
                      std::list<Entity> &enemies) {
  // Clear screen
  SDL_SetRenderDrawColor(sdl_renderer, 0x20, 0x20, 0x20, 0xFF);
  SDL_RenderClear(sdl_renderer);


  // Render player
  player.Render();
  // Render enemies
  for (auto &enemy: enemies) {
    enemy.Render();
  }
  // Render entities
  for (auto &entity: entities) {
    entity.Render();
  }

  // Update Screen
  SDL_RenderPresent(sdl_renderer);
}
#endif

void Renderer::UpdateWindowTitle(int fps)
{
    std::string title{"FPS: " + std::to_string(fps)};
    SDL_SetWindowTitle(sdl_window, title.c_str());
}
