#include <iostream>

#include "config.h"
#include "controller.h"
#include "game.h"
#include "renderer.h"

int main() {

  Renderer renderer(Config::kScreenWidth, Config::kScreenHeight,
                    Config::kGridWidth, Config::kGridHeight);
  Controller controller;
  Game game(Config::kGridWidth, Config::kGridHeight, renderer);
  game.Run(controller, Config::kMsPerFrame);
  std::cout << "Game has terminated successfully!\n";
  std::cout << "Score: " << game.GetScore() << "\n";
  std::cout << "Size: " << game.GetSize() << "\n";
  return 0;
}