#define SDL_MAIN_HANDLED
#include <iostream>

// #include "config.h"
// #include "controller.h"
#include "game.h"
// #include "renderer.h"

int main() {

  // Renderer renderer(Config::kScreenWidth, Config::kScreenHeight);
  // Controller controller;
  // Game game(renderer);
  // game.Run(controller, Config::kMsPerFrame);
  Game game;
  game.Run();
  std::cout << "Game has terminated successfully!\n";
  // std::cout << "Score: " << game.GetScore() << "\n";
  // std::cout << "Size: " << game.GetSize() << "\n";
  return 0;
}