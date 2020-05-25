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
  : running_(true),
    eng_(dev_()),
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
            renderer_->UpdateWindowTitle(frame_count);
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
    for (auto &actor: actors_) {
        actor->ProcessInput(keyboardState);
    }
}

void Game::Update() {
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


        // Entity enemy(*enemy_texture_.get(),
        //              renderer_->GetScreenWidth(),
        //              renderer_->GetScreenHeight());
        // enemy.x = renderer_->GetScreenWidth();
        // enemy.y = random_y_(eng_);
        // enemy.dx = random_dx_(eng_);
        // enemy.dy = 0;//random_dy_(eng_);
        // enemy.health = 1;
        // enemy.side = Entity::Side::kEnemy;
        // enemies_.emplace_back(std::move(enemy));

        alienSpawnTimer_ = random_timer_(eng_);
    }
}

void Game::DetectBulletCollision(BulletActor *bullet) {
    for (auto &actor: actors_) {
        if (bullet->side != actor->side) {
            SDL_Rect a{actor->GetRect()};
            SDL_Rect b{bullet->GetRect()};
            if (SDL_HasIntersection(&a, &b)) {
                actor->isAlive = false;
                bullet->isAlive = false;
            }
        }
    }
}

#if 0
void Game::UpdateGame() {

    if (player_->health <= 0) {
        enemies_.clear();
        entities_.clear();
        player_->health = 2;
        return;
    }
    player_->Update();
    if (player_->fire && player_->reload == 0) {
        FireBullet();
    }

    for (auto &enemy: enemies_) {
        enemy.Update();
        if (enemy.reload <= 0) {
            FireAlienBullet(enemy);
        }
    }
    enemies_.remove_if([](Entity &e){ return e.health == 0; });

    for (auto &entity: entities_) {
        entity.Update();
        if (entity.health && BulletHitFighter(entity)) {
            entity.health = 0;
        }
    }
    entities_.remove_if([](Entity &e){ return e.health == 0; });

    SpawnEnemies();
}

void Game::GenerateOutput() {
    renderer_->Render(*player_.get(), entities_, enemies_);
}

bool Game::BulletHitFighter(Entity &b) {
    for (auto &e: enemies_) {
        if (e.side != b.side
           && Collision(b.x, b.y, b.w, b.h, e.x, e.y, e.w, e.h)) {
            b.health = 0;
            e.health--;
            e.health = e.health < 0 ? 0 : e.health;
            return true;
        }
    }
    Player &e = *player_.get();
    if (e.side != b.side
        && Collision(b.x, b.y, b.w, b.h, e.x, e.y, e.w, e.h)) {
        b.health = 0;
        e.health--;
        e.health = e.health < 0 ? 0 : e.health;
        return true;
    }
    return false;
}

void Game::CalcSlope(int x1, int y1, int x2, int y2, float *dx, float *dy)
{
	int steps = std::max(abs(x1 - x2), abs(y1 - y2));

	if (steps == 0)
	{
		*dx = *dy = 0;
		return;
	}

	*dx = (x1 - x2);
	*dx /= steps;

	*dy = (y1 - y2);
	*dy /= steps;
}

bool Game::Collision(int x1, int y1, int w1, int h1,
                     int x2, int y2, int w2, int h2) {
    return (std::max(x1, x2) < std::min(x1 + w1, x2 + w2))
            && (std::max(y1, y2) < std::min(y1 + h1, y2 + h2));
}

void Game::FireAlienBullet(Entity &e) {
    Entity bullet(*alien_bullet_texture_.get(),
                  renderer_->GetScreenWidth(),
                  renderer_->GetScreenHeight());
    bullet.x = e.x;// + e.w - Config::kBulletSpeed;
	bullet.y = e.y;
	bullet.health = 1;
    bullet.side = e.side;

    bullet.x += (e.w / 2) - (bullet.w / 2);
	bullet.y += (e.h / 2) - (bullet.h / 2);
    if (e.x - player_->x < 100) {
        return;
    }
    CalcSlope(player_->x + (player_->w / 2), player_->y + (player_->h / 2), e.x, e.y, &bullet.dx, &bullet.dy);

	bullet.dx *= Config::kAlienBulletSpeed;
    bullet.dy *= Config::kAlienBulletSpeed;

	e.reload = random_alien_bullet_(eng_);
    entities_.emplace_back(std::move(bullet));
}

void Game::FireBullet() {
    Entity bullet(*bullet_texture_.get(),
                  renderer_->GetScreenWidth(),
                  renderer_->GetScreenHeight());
    bullet.x = player_->x + player_->w - Config::kBulletSpeed;
	bullet.y = player_->y;
	bullet.dx = Config::kBulletSpeed;
	bullet.health = 1;
    bullet.side = Entity::Side::kPlayer;

	bullet.y += (player_->h / 2) - (bullet.h / 2);

	player_->reload = 8;
    entities_.emplace_back(std::move(bullet));
}

void Game::SpawnEnemies() {
    if (--enemySpawnTimer_ <= 0) {
        Entity enemy(*enemy_texture_.get(),
                     renderer_->GetScreenWidth(),
                     renderer_->GetScreenHeight());
        enemy.x = renderer_->GetScreenWidth();
        enemy.y = random_y_(eng_);
        enemy.dx = random_dx_(eng_);
        enemy.dy = 0;//random_dy_(eng_);
        enemy.health = 1;
        enemy.side = Entity::Side::kEnemy;
        enemies_.emplace_back(std::move(enemy));

        enemySpawnTimer_ = random_timer_(eng_);
    }
}
#endif
