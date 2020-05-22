#include "controller.h"

#include <iostream>

#include "SDL.h"



void Controller::HandleInput(bool &running, Player &player) {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        switch (e.type)
        {
            case SDL_QUIT:
                running = false;
                break;
            case SDL_KEYDOWN:
                KeyDown(e.key, player);
                break;
            case SDL_KEYUP:
                KeyUp(e.key, player);
                break;
            default:
                break;
        }
    }
}

void Controller::KeyDown(SDL_KeyboardEvent &event, Player &player) {
    if (event.repeat == 0) {
		if (event.keysym.scancode == SDL_SCANCODE_UP) {
			player.up = true;
		} else if (event.keysym.scancode == SDL_SCANCODE_DOWN) {
			player.down = true;
		} else if (event.keysym.scancode == SDL_SCANCODE_LEFT) {
			player.left = true;
		} else if (event.keysym.scancode == SDL_SCANCODE_RIGHT) {
			player.right = true;
		} else if (event.keysym.scancode == SDL_SCANCODE_LCTRL) {
            player.fire = true;
        }
	}
}

void Controller::KeyUp(SDL_KeyboardEvent &event, Player &player) {
    if (event.repeat == 0) {
		if (event.keysym.scancode == SDL_SCANCODE_UP) {
			player.up = false;
		} else if (event.keysym.scancode == SDL_SCANCODE_DOWN) {
			player.down = false;
		} else if (event.keysym.scancode == SDL_SCANCODE_LEFT) {
			player.left = false;
		} else if (event.keysym.scancode == SDL_SCANCODE_RIGHT) {
			player.right = false;
		} else if (event.keysym.scancode == SDL_SCANCODE_LCTRL) {
            player.fire = false;
        }
	}
}
