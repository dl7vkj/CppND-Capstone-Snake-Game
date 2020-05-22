#include "game.h"

#include <iostream>
#include <cstdint>
#include <memory>
#include <functional>

#include "SDL.h"

#include "config.h"
#include "sdl_texture.h"




Game::Game(Renderer &renderer)
  : renderer_(renderer),
    player_texture_(std::make_unique<SDLTexture>(
        Config::kPlayerImage, *renderer_.GetSDLRenderer())),
    bullet_texture_(std::make_unique<SDLTexture>(
        Config::kBulletImage, *renderer_.GetSDLRenderer())),
    enemy_texture_(std::make_unique<SDLTexture>(
        Config::kEnemyImage, *renderer_.GetSDLRenderer())),
    player_(*player_texture_.get(),
           renderer_.GetWidth(),
           renderer_.GetHeight()),
    eng_(dev_()),
    random_y_(0, renderer_.GetHeight()),
    random_dx_(-5, -2),
    random_dy_(-2, +2),
    random_timer_(30, 90)
{
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

    // players_.emplace_back(*player_texture_.get(),
    //                       renderer_.GetWidth(),
    //                       renderer_.GetHeight());
    player_.SetPosition(100, 100);
    // entities_.emplace_back(*bullet_texture_.get(),
    //                       renderer_.GetWidth(),
    //                       renderer_.GetHeight());

    // Player &player = players_.front();
    // Entity &bullet = entities_.front();

    while (running) {
        frame_start = SDL_GetTicks();

        // Input, Update, Render - the main game loop.
        controller.HandleInput(running, player_);
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
        renderer_.Render(player_, entities_);

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

void Game::FireBullet() {
    Entity bullet(*bullet_texture_.get(),
                  renderer_.GetWidth(),
                  renderer_.GetHeight());
    bullet.x = player_.x + player_.w - Config::kBulletSpeed;
	bullet.y = player_.y;
	bullet.dx = Config::kBulletSpeed;
	bullet.health = 1;

	bullet.y += (player_.h / 2) - (bullet.h / 2);

	player_.reload = 8;
    entities_.emplace_back(std::move(bullet));
}

void Game::SpawnEnemies() {
    if (--enemySpawnTimer_ <= 0) {
        Entity enemy(*enemy_texture_.get(),
                     renderer_.GetWidth(),
                     renderer_.GetHeight());
        enemy.x = renderer_.GetWidth();
        enemy.y = random_y_(eng_);
        enemy.dx = random_dx_(eng_);
        enemy.dy = random_dy_(eng_);
        enemy.health = 1;
        entities_.emplace_back(std::move(enemy));

        enemySpawnTimer_ = random_timer_(eng_);
    }
}

void Game::Update() {
    player_.Update();
    if (player_.fire && player_.reload == 0) {
        FireBullet();
    }

    // for (auto &enemy: enemies_) {
    //     enemy.Update();
    // }
    // enemies_.remove_if([](Entity &e){ return e.health == 0; });

    for (auto &entity: entities_) {
        entity.Update();
    }
    entities_.remove_if([](Entity &e){ return e.health == 0; });

    SpawnEnemies();
}
