#ifndef GAME_H
#define GAME_H

#include <random>
// #include <vector>
#include <list>

#include "SDL.h"

#include "controller.h"
#include "renderer.h"
#include "player.h"
#include "entity.h"


class Game {
public:
    Game(Renderer &renderer);
    void Run(Controller &controller,
            std::size_t target_frame_duration);
    // int GetScore() const;
    // int GetSize() const;

private:
    Renderer &renderer_;
    std::unique_ptr<SDLTexture> player_texture_;
    std::unique_ptr<SDLTexture> bullet_texture_;
    std::unique_ptr<SDLTexture> enemy_texture_;
    Player player_;
    std::list<Entity> entities_;
    // std::list<Entity> enemies_;
    int enemySpawnTimer_{0};

    // SDL_Point food;

    std::random_device dev_;
    std::mt19937 eng_;
    std::uniform_int_distribution<int> random_y_;
    std::uniform_int_distribution<int> random_dx_;
    std::uniform_int_distribution<int> random_dy_;
    std::uniform_int_distribution<int> random_timer_;

    // int score{0};

    // void PlaceFood();
    void FireBullet();
    void SpawnEnemies();
    void Update();
};

#endif