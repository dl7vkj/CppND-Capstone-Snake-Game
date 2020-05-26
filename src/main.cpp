#define SDL_MAIN_HANDLED
#include <iostream>

#include "game.h"


int main() {
    Game game;
    game.Run();
    std::cout << "Game has terminated successfully!\n";
    // std::cout << "Score: " << game.GetScore() << "\n";
    // std::cout << "Size: " << game.GetSize() << "\n";
    return EXIT_SUCCESS;
}
