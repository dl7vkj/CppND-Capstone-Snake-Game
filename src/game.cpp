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

#include "game_object.h"
#include "none_input_component.h"
#include "none_physics_component.h"
#include "none_graphics_component.h"
#include "player_input_component.h"
#include "player_physics_component.h"
#include "texture_graphics_component.h"
#include "bullet_physics_component.h"
#include "alien_physics_component.h"
#include "star_physics_component.h"
#include "star_graphics_component.h"


Game::Game()
  : renderer_(Config::kScreenWidth, Config::kScreenHeight),
    eng_(dev_()),
    random_y_(0, Config::kScreenHeight - 32),
    random_dx_(-6.0f, -3.5f),
    random_dy_(-2.0f, +2.0f),
    random_timer_(30, 90),
    random_alien_bullet_(30, 120)
{
    CreateBackgound();

    //Create the player
    // Get texture for player
    Texture *texture = renderer_.GetTextureHandle(Config::kPlayerImage);
    // Create input component for player
    auto input = std::make_unique<PlayerInputComponent>();
    // Create physics component for player
    auto physics = std::make_unique<PlayerPhysicsComponent>();
    // Create graphics component for player
    auto graphics = std::make_unique<TextureGraphicsComponent>(texture);
    // Create player game object
    auto obj = std::make_unique<GameObject>(std::move(input),
                                            std::move(physics),
                                            std::move(graphics));
    // Register the player to the renderer system
    renderer_.RegisterGameObjects(obj.get());
    // Set players position
    obj->x = 100;
    obj->y = Config::kScreenHeight/2;
    // Set players dimensions
    obj->w = texture->GetWidth();
    obj->h = texture->GetHeight();
    // Set players side
    obj->side = GameObject::Side::kPlayer;
    // Set players health
    obj->health = kPlayerHealth;
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
            renderer_.UpdateWindowTitle(objs_[0]->health, score_, remainingLives_, frame_count);
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
            auto &player = objs_[0];
            player->isAlive = true;
            player->health = kPlayerHealth;
            remainingLives_ = kRemainingLives;
            player->fireBullet = false;
            player->x = 100;
            player->y = renderer_.GetScreenHeight()/2;
            state_ = kPlay;
        }
    }

    // NOTE: In this game only the player consumes input.
    //       So don't wasting time to iterate over all game objects...
    if (objs_.size() > 0 && state_ == kPlay) {
        auto &player = objs_[0];
        player->ProcessInput(keyboardState);
    }
}

void Game::Update() {

    // Update background stars
    background_->UpdatePhysics(*this);

    if (state_ == kPlay) {
        // Move pending game objects to objs_
        std::move(pendingObjs_.begin(), pendingObjs_.end(),
                    std::back_inserter(objs_));
        pendingObjs_.clear();

        // Update game objects
        for (auto &obj: objs_) {
            obj->UpdatePhysics(*this);
        }
        // Update bullets
        for (auto &bullet: bullets_) {
            bullet->UpdatePhysics(*this);
            DetectBulletCollision(bullet.get());
        }

        // Remove died bullets and unregister them from renderer
        bullets_.erase(std::remove_if(bullets_.begin(), bullets_.end(),
            [&](auto const &x){
                if (!x->isAlive) {
                    renderer_.UnregisterGameObjects(x.get());
                    return true;
                }
                return false;
            }), bullets_.end());

        // Remove & Unregister died GameObjects
        // objs_[0] is our player so don't remove him
        objs_.erase(std::remove_if(objs_.begin()+1, objs_.end(),
            [&](auto const &x){
                if (!x->isAlive) {
                    renderer_.UnregisterGameObjects(x.get());
                    return true;
                }
                return false;
            }), objs_.end());

        auto &player = objs_[0];


        if (player->health <= 0) {
            state_ = kRespawn;
            player->fireBullet = false;
            Clear();
            remainingLives_--;
            if (remainingLives_ < 0) {
                state_ = kPause;
            }
            return;
        }

        SpawnAliens();
    } else if (state_ == kRespawn) {
        if (--respawnTimer_ <= 0){
            auto &player = objs_[0];
            state_ = kPlay;
            respawnTimer_ = kRespawnTime;
            player->fireBullet = false;
            player->isAlive = true;
            player->health = kPlayerHealth;
        }
    }
}

void Game::Output() {
    renderer_.Render();
}

void Game::Clear() {
    // Remove & Unregister pending GameObjects
    pendingObjs_.erase(std::remove_if(pendingObjs_.begin(), pendingObjs_.end(),
        [&](auto const &x){
            renderer_.UnregisterGameObjects(x.get());
            return true;
        }), pendingObjs_.end());

    // Remove bullets and unregister them from renderer
    bullets_.erase(std::remove_if(bullets_.begin(), bullets_.end(),
        [&](auto const &x){
            renderer_.UnregisterGameObjects(x.get());
            return true;
        }), bullets_.end());

    // Remove & Unregister GameObjects
    // objs_[0] is our player so don't remove him
    objs_.erase(std::remove_if(objs_.begin()+1, objs_.end(),
        [&](auto const &x){
            renderer_.UnregisterGameObjects(x.get());
            return true;
        }), objs_.end());
}

void Game::FireBullet(float x, float y, float dx, float dy,
                      GameObject::Side side) {
    // Get texture for bullet
    Texture *texture;
    if (side == GameObject::Side::kPlayer) {
        texture = renderer_.GetTextureHandle(Config::kBulletImage);
    } else {
        texture = renderer_.GetTextureHandle(Config::kAlienBulletImage);
    }
    // Create input component for bullet
    auto input = std::make_unique<NoneInputComponent>();
    // Create physics component for bullet
    auto physics = std::make_unique<BulletPhysicsComponent>();
    // Create graphics component for bullet
    auto graphics = std::make_unique<TextureGraphicsComponent>(texture);
    // Create bullet game object
    auto obj = std::make_unique<GameObject>(std::move(input),
                                            std::move(physics),
                                            std::move(graphics));
    // Register the bullet to the renderer system
    renderer_.RegisterGameObjects(obj.get());
    // Set bullets dimensions
    obj->w = texture->GetWidth();
    obj->h = texture->GetHeight();
    // Set bullets position
    if (side == GameObject::Side::kPlayer) {
        obj->x = x;
    } else {
        obj->x = x - (obj->w / 2.0f);
    }
    obj->y = y - (obj->h / 2.0f);
    // Set bullets velocity
    obj->dx = dx;
    obj->dy = dy;
    // Set bullets side
    obj->side = side;
    // Add bullet to game
    AddBullet(std::move(obj));
}

void Game::SpawnAliens() {
    if (--alienSpawnTimer_ <= 0) {
        // Create an alien
        // Get texture for alien
        Texture *texture = renderer_.GetTextureHandle(Config::kEnemyImage);
        // Create input component for alien
        auto input = std::make_unique<NoneInputComponent>();
        // Create physics component for alien
        auto physics = std::make_unique<AlienPhysicsComponent>();
        // Create graphics component for alien
        auto graphics = std::make_unique<TextureGraphicsComponent>(texture);
        // Create alien game object
        auto obj = std::make_unique<GameObject>(std::move(input),
                                                std::move(physics),
                                                std::move(graphics));
        // Register the alien to the renderer system
        renderer_.RegisterGameObjects(obj.get());
        // Set aliens dimensions
        obj->w = texture->GetWidth();
        obj->h = texture->GetHeight();
        // Set aliens position
        obj->x = renderer_.GetScreenWidth();
        obj->y = random_y_(eng_);
        // Set aliens velocity
        obj->dx = random_dx_(eng_);
        obj->dy = random_dy_(eng_);
        // Set aliens side
        obj->side = GameObject::Side::kAlien;
        // Add alien to game
        AddGameObject(std::move(obj));
        // Reset spwan timer
        alienSpawnTimer_ = random_timer_(eng_);
    }
}


// TODO: REFACTOR
void Game::DetectBulletCollision(GameObject *bullet) {
    // Bullets can only hit once
    if (bullet->health <= 0)
        return;
    // Iterate over all GameObjects
    for (auto &obj: objs_) {
        // No friendly fire.
        if (bullet->side != obj->side) {
            SDL_Rect a;
            SDL_Rect b;
            // Area of GameObject
            a.x = static_cast<int>(obj->x);
            a.y = static_cast<int>(obj->y);
            a.w = obj->w;
            a.h = obj->h;
            // Area of bullet
            b.x = static_cast<int>(bullet->x);
            b.y = static_cast<int>(bullet->y);
            b.w = bullet->w;
            b.h = bullet->h;
            // Check if both areas intersect
            if (SDL_HasIntersection(&a, &b)) {
                // yes, bullet hit target
                obj->health--;
                bullet->health--;
                if (obj->side == GameObject::Side::kAlien) {
                    // We hit an alien!
                    score_++;
                }
            }
        }
    }
}

void Game::CreateBackgound() {
    // Create input component for star
    auto input = std::make_unique<NoneInputComponent>();
    // Create physics component for star
    auto physics = std::make_unique<StarPhysicsComponent>(*this);
    // Create graphics component for star
    auto graphics = std::make_unique<StarGraphicsComponent>(physics.get());
    // Create star object
    background_ = std::make_unique<GameObject>(std::move(input),
                                            std::move(physics),
                                            std::move(graphics));
    // Register the star to the renderer system
    renderer_.RegisterGameObjects(background_.get());
    // Set stars side
    background_->side = GameObject::Side::kNeutral;
}
