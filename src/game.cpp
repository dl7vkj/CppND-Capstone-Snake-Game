#include "game.h"

#include <iostream>
#include <cstdint>

#include "SDL.h"

#include "config.h"




Game::Game(Renderer &renderer, std::size_t screen_width,
           std::size_t screen_height)
    : renderer_(renderer),
      player_(renderer_.MakeTexture(Config::kPlayerImage),
              screen_width, screen_height) {}

void Game::Run(Controller const &controller,
               std::size_t target_frame_duration)
{
    Uint32 title_timestamp = SDL_GetTicks();
    Uint32 frame_start;
    Uint32 frame_end;
    Uint32 frame_duration;
    int frame_count = 0;
    bool running = true;

    player_.SetPosition(100, 100);

    while (running) {
        frame_start = SDL_GetTicks();

        // Input, Update, Render - the main game loop.
        controller.HandleInput(player_, running);
        Update();
        renderer_.Render(player_);

        frame_end = SDL_GetTicks();

        // Keep track of how long each loop through the input/update/render cycle
        // takes.
        frame_count++;
        frame_duration = frame_end - frame_start;

        // After every second, update the window title.
        if (frame_end - title_timestamp >= 1000) {
            renderer_.UpdateWindowTitle(frame_count);
            frame_count = 0;
            title_timestamp = frame_end;
        }

        // If the time for this frame is too small (i.e. frame_duration is
        // smaller than the target ms_per_frame), delay the loop to
        // achieve the correct frame rate.
        if (frame_duration < target_frame_duration) {
            SDL_Delay(target_frame_duration - frame_duration);
        }
    }
}

void Game::Update() {
    player_.Update();
}
