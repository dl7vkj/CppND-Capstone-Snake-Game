#include "game.h"

#include <iostream>
#include <cstdint>
#include <memory>
#include <functional>
#include <algorithm>
#include <type_traits>

#include "SDL.h"

#include "config.h"
#include "texture.h"
// #include "SDL_ttf.h"

// #include "actor.h"
// #include "player.h"
// #include "alien_actor.h"
// #include "move_component.h"
// #include "texture_component.h"
// #include "fence_component.h"
// #include "star.h"

#include "game_object.h"
#include "none_input_component.h"
#include "none_physics_component.h"
#include "none_graphics_component.h"
#include "player_input_component.h"
#include "player_physics_component.h"
#include "texture_graphics_component.h"


// template <typename A, typename B, typename C>
// GameObject &CreateGameObject(Game &game) {
//     auto input = std::make_unique<A>();
//     auto physics = std::make_unique<B>();
//     auto graphics = std::make_unique<C>();
//     auto obj = std::make_unique<GameObject>(std::move(input),
//                                             std::move(physics),
//                                             std::move(graphics));

//     // NOTE: Do not register 'none' components
//     // if constexpr (!std::is_same_v<A, NoneInputsComponent>) {
//     //     game.GetController().RegisterInputComponent(input.get());
//     // }
//     // if constexpr (!std::is_same_v<B, NonePhysicsComponent>) {
//     //     game.RegisterPhysicsComponent(physics.get());
//     // }
//     if constexpr (!std::is_same_v<C, NoneGraphicsComponent>) {
//         game.GetRenderer().RegisterGameObjects(obj.get());
//     }
//     GameObject &retval = *obj.get();
//     game.AddGameObject(std::move(obj));
//     return retval;
// }


Game::Game()
  : renderer_(Config::kScreenWidth, Config::kScreenHeight),
    eng_(dev_()),
    random_y_(0, Config::kScreenHeight),
    random_dx_(-6.0f, -3.5f),
    random_dy_(-2.0f, +2.0f),
    random_timer_(30, 90),
    random_alien_bullet_(30, 120)
{
    // Create the renderer
    // renderer_ = std::make_unique<Renderer>(Config::kScreenWidth,
    //                                        Config::kScreenHeight);

    // Create the player
    // CreateGameObject<PlayerInputComponent, PlayerPhysicsComponent,
    //                  PlayerGraphicsComponent>(*this);

    // // Create the background stars
    // std::uniform_int_distribution<int> dist{0, std::numeric_limits<int>::max()};
    // for (int i = 0; i < 500; i++) {
    //     int x = dist(eng_) % Config::kScreenWidth;
    //     int y = dist(eng_) % Config::kScreenHeight;
    //     float speed = (10 + dist(eng_) % 20)*0.1f;
    //     auto star = std::make_unique<Star>(this, -speed, Config::kScreenWidth);
    //     star->SetPosition(x, y);
    //     // bgStars_.emplace_back(std::move(star));
    //     bgStars_.emplace_back(std::move(star));
    // }

    // // Create the player
    // auto player = std::make_unique<Player>(this);
    // SDL_FPoint start_pos{100.0f, 100.0f};
    // player->SetPosition(start_pos);
    // player->health = kPlayerHealth;
    // // player_ = player.get();
    // AddActor(std::move(player));

    // Get texture for player
    Texture *texture = renderer_.GetTexture(Config::kPlayerImage);
    // Create input component for player
    auto input = std::make_unique<PlayerInputComponent>();
    // Create physics component for player
    auto physics = std::make_unique<PlayerPhysicsComponent>(texture->GetWidth(),
                                                            texture->GetHeight(),
                                                            Config::kScreenWidth,
                                                            Config::kScreenHeight);
    // Create graphics component for player
    auto graphics = std::make_unique<TextureGraphicsComponent>(texture);
    // Create player game object and move components to game object
    auto obj = std::make_unique<GameObject>(std::move(input),
                                            std::move(physics),
                                            std::move(graphics));
    // Register the player to the renderer system
    renderer_.RegisterGameObjects(obj.get());
    // Set players position
    obj->x = 100;
    obj->y = Config::kScreenHeight/2;
    // Set players dimensions
    // obj->w = texture->GetWidth();
    // obj->h = texture->GetHeight();
    // Add player to game
    AddGameObject(std::move(obj));
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
            // renderer_->UpdateWindowTitle(actors_[0]->health, score_, remainingLives_, frame_count);
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

    // if (state_ == kPause) {
    //     if (keyboardState[SDL_SCANCODE_SPACE]) {
    //         auto &player = actors_[0];
    //         player->isAlive = true;
    //         player->health = kPlayerHealth;
    //         remainingLives_ = kRemainingLives;
    //         player->SetPosition(100, renderer_->GetScreenHeight()/2);
    //         state_ = kPlay;
    //     }
    // }

    // if (state_ == kPlay) {
    //     for (auto &actor: actors_) {
    //         actor->ProcessInput(keyboardState);
    //     }
    // }
    // NOTE: In this game only the player consumes input.
    //       So don't wasting time to iterate over all game objects...
    if (objs_.size() > 0) {
        auto &player = objs_[0];
        player->ProcessInput(keyboardState);
    }
}

void Game::Update() {

    // Move pending game objects to objs_
    std::move(pendingObjs_.begin(), pendingObjs_.end(), std::back_inserter(objs_));
    pendingObjs_.clear();

    // Update game objects physics
    for (auto &obj: objs_) {
        obj->UpdatePhysics(*this);
    }

    // Move pending game objects to objs_
    // objs_.insert(pendingObjs_.end(),
    //              std::make_move_iterator(pendingObjs_.begin()),
    //              std::make_move_iterator(pendingObjs_.end()));
    //pendingObjs_.clear();

    // Add pending game objects to objs_
    // std::reverse(pendingObjs_.begin(), pendingObjs_.end());
    // while (pendingObjs_.empty() == false) {
    //     objs_.emplace_back(std::move(pendingObjs_.back()));
    //     pendingObjs_.pop_back();
    // }

    // // Update background stars
    // for (auto &star: bgStars_) {
    //     star->Update();
    // }

    // if (state_ == kPlay) {

    //     for (auto &actor: actors_) {
    //         actor->Update();
    //     }

    //     for (auto &bullet: bullets_) {
    //         bullet->Update();
    //         DetectBulletCollision(bullet.get());
    //     }

    //     SpawnAliens();

    //     // Add pending actors
    //     std::reverse(pendingActors_.begin(), pendingActors_.end());
    //     while (pendingActors_.empty() == false) {
    //         actors_.emplace_back(std::move(pendingActors_.back()));
    //         pendingActors_.pop_back();
    //     }


    //     auto &player = actors_[0];

    //     if (remainingLives_ < 0) {
    //         state_ = kPause;
    //         actors_.erase(actors_.begin()+1, actors_.end());
    //         bullets_.erase(bullets_.begin(), bullets_.end());
    //         return;
    //     } else if (player->health <= 0) {
    //         state_ = kRespawn;
    //         actors_.erase(actors_.begin()+1, actors_.end());
    //         bullets_.erase(bullets_.begin(), bullets_.end());
    //         remainingLives_--;
    //         return;
    //     }

    //     // Add pending bullets
    //     std::reverse(pendingBullets_.begin(), pendingBullets_.end());
    //     while (pendingBullets_.empty() == false) {
    //         bullets_.emplace_back(std::move(pendingBullets_.back()));
    //         pendingBullets_.pop_back();
    //     }

    //     // Remove died actors, [0] is our player so don't remove him
    //     actors_.erase(std::remove_if(actors_.begin()+1, actors_.end(),
    //         [](auto const &a){ return a->isAlive == false; }), actors_.end());

    //     // Remove hitting bullets
    //     bullets_.erase(std::remove_if(bullets_.begin(), bullets_.end(),
    //         [](auto const &a){ return a->isAlive == false; }), bullets_.end());
    // } else if (state_ == kRespawn) {
    //     if (--respawnTimer_ <= 0){
    //         auto &player = actors_[0];
    //         state_ = kPlay;
    //         respawnTimer_ = kRespawnTime;
    //         player->isAlive = true;
    //         player->health = kPlayerHealth;
    //     }
    // }
}

void Game::Output() {
    renderer_.Render();
}

// void Game::SpawnAliens() {
//     if (--alienSpawnTimer_ <= 0) {
//         // Create the alien
//         auto alien = std::make_unique<AlienActor>(this);
//         alien->SetPosition(renderer_->GetScreenWidth(), random_y_(eng_));
//         alien->SetVelocity(random_dx_(eng_), random_dy_(eng_));
//         AddActor(std::move(alien));
//         alienSpawnTimer_ = random_timer_(eng_);
//     }
// }

// void Game::DetectBulletCollision(BulletActor *bullet) {
//     for (auto &actor: actors_) {
//         if (bullet->health > 0 && bullet->side != actor->side) {
//             SDL_Rect a{actor->GetRect()};
//             SDL_Rect b{bullet->GetRect()};
//             if (SDL_HasIntersection(&a, &b)) {
//                 actor->health--;
//                 bullet->health--;
//                 if (actor->side == Actor::Side::kAlien) {
//                     score_++;
//                 }
//             }
//         }
//     }
// }
