#include "controller.h"
#include <iostream>
#include "SDL.h"

// void Controller::ChangeDirection(Snake &snake, Snake::Direction input,
//                                  Snake::Direction opposite) const {
//   if (snake.direction != opposite || snake.size == 1) snake.direction = input;
//   return;
// }

void Controller::HandleInput(Player &player, bool &running) const {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        switch (e.type)
        {
            case SDL_QUIT:
                running = false;
                break;
            case SDL_KEYDOWN:
                KeyDown(player, e.key);
                break;
            case SDL_KEYUP:
                KeyUp(player, e.key);
                break;
            default:
                break;
        }
        // if (e.type == SDL_QUIT) {
        //   running = false;
        // } else if (e.type == SDL_KEYDOWN) {
        //   switch (e.key.keysym.sym) {
        //     // case SDLK_UP:
        //     //   ChangeDirection(snake, Snake::Direction::kUp,
        //     //                   Snake::Direction::kDown);
        //     //   break;

        //     // case SDLK_DOWN:
        //     //   ChangeDirection(snake, Snake::Direction::kDown,
        //     //                   Snake::Direction::kUp);
        //     //   break;

        //     // case SDLK_LEFT:
        //     //   ChangeDirection(snake, Snake::Direction::kLeft,
        //     //                   Snake::Direction::kRight);
        //     //   break;

        //     // case SDLK_RIGHT:
        //     //   ChangeDirection(snake, Snake::Direction::kRight,
        //     //                   Snake::Direction::kLeft);
        //     //   break;
        //   }
        // }
    }
}

void Controller::KeyDown(Player &player, SDL_KeyboardEvent &event) const {
    if (event.repeat == 0) {
		if (event.keysym.scancode == SDL_SCANCODE_UP) {
			player.up = true;
		} else if (event.keysym.scancode == SDL_SCANCODE_DOWN) {
			player.down = true;
		} else if (event.keysym.scancode == SDL_SCANCODE_LEFT) {
			player.left = true;
		} else if (event.keysym.scancode == SDL_SCANCODE_RIGHT) {
			player.right = true;
		}
	}
}

void Controller::KeyUp(Player &player, SDL_KeyboardEvent &event) const {
    if (event.repeat == 0) {
		if (event.keysym.scancode == SDL_SCANCODE_UP) {
			player.up = false;
		} else if (event.keysym.scancode == SDL_SCANCODE_DOWN) {
			player.down = false;
		} else if (event.keysym.scancode == SDL_SCANCODE_LEFT) {
			player.left = false;
		} else if (event.keysym.scancode == SDL_SCANCODE_RIGHT) {
			player.right = false;
		}
	}
}
