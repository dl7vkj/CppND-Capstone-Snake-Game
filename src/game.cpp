#include "game.h"

#include <iostream>
#include <cstdint>
#include <memory>
#include <functional>

#include "SDL.h"

#include "config.h"
#include "sdl_texture.h"




Game::Game(Renderer &renderer) : renderer_(renderer) {

    player_texture_ = std::make_unique<SDLTexture>(
        Config::kPlayerImage, *renderer_.GetSDLRenderer());
    bullet_texture_ = std::make_unique<SDLTexture>(
        Config::kBulletImage, *renderer_.GetSDLRenderer());
}

void Game::Run(Controller &controller,
               std::size_t target_frame_duration)
{
    Uint32 title_timestamp = SDL_GetTicks();
    Uint32 frame_start;
    Uint32 frame_end;
    Uint32 frame_duration;
    int frame_count = 0;
    bool running = true;

    // player_.SetPosition(100, 100);
    // SDLTexture player_texture(Config::kPlayerImage, *renderer_.GetSDLRenderer());
    // SDLTexture bullet_texture(Config::kPlayerImage, *renderer_.GetSDLRenderer());

    players_.emplace_back(*player_texture_.get(),
                          renderer_.GetWidth(),
                          renderer_.GetHeight());
    players_.back().SetPosition(100, 100);
    // entities_.emplace_back(*bullet_texture_.get(),
    //                       renderer_.GetWidth(),
    //                       renderer_.GetHeight());

    Player &player = players_.front();
    // Entity &bullet = entities_.front();

    while (running) {
        frame_start = SDL_GetTicks();

        // Input, Update, Render - the main game loop.
        controller.HandleInput(running, players_, entities_);
        // if (player.fire && bullet.health == 0)
        // {
        //     bullet.x = player.x + player.w;
		// 	bullet.y = player.y + player.h/2 - bullet.h/2;
		// 	bullet.dx = 16;
        //     bullet.x -= bullet.dx;
		// 	bullet.dy = 0;
		// 	bullet.health = 1;
        // }
        Update();
        renderer_.Render(players_, entities_);

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
    for (auto &player: players_) {
        player.Update();
        if (player.fire && player.reload == 0) {
            FireBullet();
        }
    }
    for (auto &entity: entities_) {
        entity.Update();
    }
    entities_.remove_if([](Entity &e){ return e.health == 0; });

}

void Game::FireBullet() {
    Player &player = players_.front();
    Entity bullet(*bullet_texture_.get(),
                  renderer_.GetWidth(),
                  renderer_.GetHeight());
    bullet.x = player.x + player.w - Config::kBulletSpeed;
	bullet.y = player.y;
	bullet.dx = Config::kBulletSpeed;
	bullet.health = 1;

	bullet.y += (player.h / 2) - (bullet.h / 2);

	player.reload = 8;
    entities_.emplace_back(std::move(bullet));
}
