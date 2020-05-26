#include "renderer.h"

#include <iostream>
#include <string>
#include <sstream>
#include <random>

#include "SDL_image.h"

#include "utility.h"

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

    // Initialize background stars
    // InitBgStars();
}

Renderer::~Renderer() {
    SDL_DestroyWindow(sdl_window);
    IMG_Quit();
    SDL_Quit();
}

void Renderer::Render() {
    SDL_SetRenderDrawColor(sdl_renderer, 0x20, 0x20, 0x20, 0xFF);
    SDL_RenderClear(sdl_renderer);

    // Render background stars
    // RenderBgStars();

    // Render textures
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

// TODO: Update HUD
void Renderer::UpdateWindowTitle(int health, int score, int life, int fps)
{
    std::ostringstream stream;
    stream << "[ Health: " << health << " | Score: " << score << " | Life: " << life << " | FPS: " << fps << " ]";
    // std::string title{"FPS: " + std::to_string(fps)};
    SDL_SetWindowTitle(sdl_window, stream.str().c_str());
}

// void Renderer::InitBgStars() {
//     std::random_device dev;
//     std::mt19937 eng{dev()};
//     std::uniform_int_distribution<int> dist{0, std::numeric_limits<int>::max()};
//     for (int i = 0; i < 500; i++) {
//         int x = dist(eng) % screenWidth_;
//         int y = dist(eng) % screenHeight_;
//         float speed = (10 + dist(eng) % 20)*0.1f;
//         auto star = std::make_unique<Star>(nullptr, -speed, screenWidth_);
//         star->SetPosition(x, y);
//         bgStars_.emplace_back(std::move(star));
//     }
// }

// void Renderer::RenderBgStars() {
//     for (auto &star: bgStars_) {
//         star->Update();
//         int c = star->GetSpeed();
//         c *= -84;
//         SDL_SetRenderDrawColor(sdl_renderer, c, c, c, 255);
//         SDL_FPoint pos{star->GetPosition()};
//         int x = pos.x;
//         int y = pos.y;
//         SDL_RenderDrawLine(sdl_renderer, x, y, x + 3/*Utility::Max(c/2, 1)*/, y);
//     }
// }
