#include "game.h"

#include <iostream>
#include <cstdint>
#include <memory>
#include <functional>
#include <algorithm>

#include "SDL.h"

#include "config.h"
#include "sdl_texture.h"
// #include "SDL_ttf.h"

#include "actor.h"
#include "player.h"
#include "alien_actor.h"
#include "move_component.h"
#include "texture_component.h"
#include "fence_component.h"

#if 0
Game::Game()
  : running_(true),
    eng_(dev_()),
    random_y_(0, Config::kScreenHeight),
    random_dx_(-5, -2),
    random_dy_(-2, +2),
    random_timer_(30, 90),
    random_alien_bullet_(0, 120)
{
    // Create the renderer
    renderer_ = std::make_unique<Renderer>(Config::kScreenWidth, Config::kScreenHeight);
    // Create the controller
    // controller_ = std::make_unique<Controller>();
    // Create textures

    player_texture_ = std::make_unique<SDLTexture>(
        Config::kPlayerImage, renderer_->GetSDLRenderer());
    bullet_texture_ = std::make_unique<SDLTexture>(
        Config::kBulletImage, renderer_->GetSDLRenderer());
    enemy_texture_ = std::make_unique<SDLTexture>(
        Config::kEnemyImage, renderer_->GetSDLRenderer());
    alien_bullet_texture_ = std::make_unique<SDLTexture>(
        Config::kAlienBulletImage, renderer_->GetSDLRenderer());
    // Create player
    player_ = std::make_unique<Player>(*player_texture_.get(),
                                        renderer_->GetScreenWidth(),
                                        renderer_->GetScreenHeight());

    // ticksCount_ = SDL_GetTicks();
}
#endif

Game::Game()
  : eng_(dev_()),
    random_y_(0, Config::kScreenHeight),
    random_dx_(-5.0f, -2.0f),
    random_dy_(-2.0f, +2.0f),
    random_timer_(30, 90),
    random_alien_bullet_(30, 120)
{
    // Create the renderer
    renderer_ = std::make_unique<Renderer>(Config::kScreenWidth,
                                           Config::kScreenHeight);

    // Create the player
    auto player = std::make_unique<Player>(this);
    SDL_FPoint start_pos{100.0f, 100.0f};
    player->SetPosition(start_pos);
    player->health = kPlayerHealth;
    // player_ = player.get();
    AddActor(std::move(player));
}

void Game::Run()
{
    // TODO: Init in constructor!
    Uint32 title_timestamp = SDL_GetTicks();
    Uint32 frame_start;
    Uint32 frame_end;
    Uint32 frame_duration;
    int frame_count = 0;

#if 0
    player_->SetPosition(100, 100);
    player_->side = Entity::Side::kPlayer;
    player_->health = 2;
#endif


    while (running_) {
        frame_start = SDL_GetTicks();
        // Input, Update, Output - the main game loop.
        Input();
        Update();
        Output();
        frame_end = SDL_GetTicks();

        // Keep track of how long each loop through the
        // input/update/render cycle takes.
        frame_count++;
        frame_duration = frame_end - frame_start;

        // TODO: Move to output
        // After every second, update the window title.
        if (frame_end - title_timestamp >= 1000) {
            renderer_->UpdateWindowTitle(actors_[0]->health, score_, remainingLives_, frame_count);
            frame_count = 0;
            title_timestamp = frame_end;
        }

        // If the time for this frame is too small (i.e. frame_duration is
        // smaller than the target ms_per_frame), delay the loop to
        // achieve the correct frame rate.
        if (frame_duration < 16) {
            SDL_Delay(16 - frame_duration);
        }
    }
}

void Game::Input() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type)
        {
            case SDL_QUIT:
                running_ = false;
                break;
            default:
                break;
        }
    }
    const uint8_t *keyboardState = SDL_GetKeyboardState(NULL);

    if (state_ == kPause) {
        if (keyboardState[SDL_SCANCODE_SPACE]) {
            auto &player = actors_[0];
            player->isAlive = true;
            player->health = kPlayerHealth;
            remainingLives_ = kRemainingLives;
            player->SetPosition(100, renderer_->GetScreenHeight()/2);
            state_ = kPlay;
        }
    }

    if (state_ == kPlay) {
        for (auto &actor: actors_) {
            actor->ProcessInput(keyboardState);
        }
    }
}

void Game::Update() {

    if (state_ == kPlay) {

        for (auto &actor: actors_) {
            actor->Update();
        }

        for (auto &bullet: bullets_) {
            bullet->Update();
            DetectBulletCollision(bullet.get());
        }

        SpawnAliens();

        // Add pending actors
        std::reverse(pendingActors_.begin(), pendingActors_.end());
        while (pendingActors_.empty() == false) {
            actors_.emplace_back(std::move(pendingActors_.back()));
            pendingActors_.pop_back();
        }


        auto &player = actors_[0];

        if (remainingLives_ < 0) {
            state_ = kPause;
            actors_.erase(actors_.begin()+1, actors_.end());
            bullets_.erase(bullets_.begin(), bullets_.end());
            return;
        } else if (player->health <= 0) {
            state_ = kRespawn;
            actors_.erase(actors_.begin()+1, actors_.end());
            bullets_.erase(bullets_.begin(), bullets_.end());
            remainingLives_--;
            return;
        }

        // Add pending bullets
        std::reverse(pendingBullets_.begin(), pendingBullets_.end());
        while (pendingBullets_.empty() == false) {
            bullets_.emplace_back(std::move(pendingBullets_.back()));
            pendingBullets_.pop_back();
        }

        // Remove died actors, [0] is our player so don't remove him
        actors_.erase(std::remove_if(actors_.begin()+1, actors_.end(),
            [](auto const &a){ return a->isAlive == false; }), actors_.end());

        // Remove hitting bullets
        bullets_.erase(std::remove_if(bullets_.begin(), bullets_.end(),
            [](auto const &a){ return a->isAlive == false; }), bullets_.end());
    } else if (state_ == kRespawn) {
        if (--respawnTimer_ <= 0){
            auto &player = actors_[0];
            state_ = kPlay;
            respawnTimer_ = kRespawnTime;
            player->isAlive = true;
            player->health = kPlayerHealth;
        }
    }
}

void Game::Output() {
    renderer_->Render();
}

void Game::SpawnAliens() {
    if (--alienSpawnTimer_ <= 0) {
        // Create the alien
        auto alien = std::make_unique<AlienActor>(this);
        alien->SetPosition(renderer_->GetScreenWidth(), random_y_(eng_));
        alien->SetVelocity(random_dx_(eng_), random_dy_(eng_));
        AddActor(std::move(alien));
        alienSpawnTimer_ = random_timer_(eng_);
    }
}

void Game::DetectBulletCollision(BulletActor *bullet) {
    for (auto &actor: actors_) {
        if (bullet->health > 0 && bullet->side != actor->side) {
            SDL_Rect a{actor->GetRect()};
            SDL_Rect b{bullet->GetRect()};
            if (SDL_HasIntersection(&a, &b)) {
                actor->health--;
                bullet->health--;
                if (actor->side == Actor::Side::kAlien) {
                    score_++;
                }
            }
        }
    }
}
