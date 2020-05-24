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
#include "move_component.h"

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
  : running_(true)
{
    // Create the renderer
    renderer_ = std::make_unique<Renderer>(Config::kScreenWidth, Config::kScreenHeight);
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


    // Create the player
    std::unique_ptr<Player> player = std::make_unique<Player>(*this);
    player->SetPosition({100.0f,100.0f});
    std::unique_ptr<MoveComponent> mvCmp = std::make_unique<MoveComponent>(*player);
    std::unique_ptr<TextureComponent> texCmp = std::make_unique<TextureComponent>(*player);
    texCmp->SetTexture(renderer_->GetTexture(Config::kPlayerImage));
    renderer_->AddTextureComponent(texCmp.get());
    actors_.emplace_back(std::move(player));


    while (running_) {
        frame_start = SDL_GetTicks();
        // Input, Update, Output - the main game loop.
        ProcessInput();
        UpdateGame();
        GenerateOutput();
        frame_end = SDL_GetTicks();

        // Keep track of how long each loop through the input/update/render cycle
        // takes.
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

void Game::ProcessInput() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type)
        {
            case SDL_QUIT:
                running_ = false;
                break;
            // case SDL_KEYDOWN:
            //     KeyDown(e.key, player);
            //     break;
            // case SDL_KEYUP:
            //     KeyUp(e.key, player);
            //     break;
            default:
                break;
        }
    }
    const uint8_t *keyboardState = SDL_GetKeyboardState(NULL);
    for (auto &actor: actors_) {
        actor->ProcessInput(keyboardState);
    }
}

void Game::UpdateGame() {
    for (auto &actor: actors_) {
        actor->Update();
    }
}

void Game::GenerateOutput() {
    renderer_->Render();
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
