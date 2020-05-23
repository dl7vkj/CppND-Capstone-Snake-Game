#ifndef GAME_H
#define GAME_H

#include <random>
// #include <vector>
#include <list>

#include "SDL.h"

// #include "controller.h"
#include "renderer.h"
#include "player.h"
#include "entity.h"


class Game {
public:
    // Game(Renderer &renderer);
    // void Run(Controller &controller,
    //         std::size_t target_frame_duration);
    Game();
    void Run();
    // int GetScore() const;
    // int GetSize() const;

private:
    void ProcessInput();
    void UpdateGame();
    void GenerateOutput();

    // Renderer &renderer_;
    std::unique_ptr<Renderer> renderer_;
    // std::unique_ptr<Controller> controller_;

    // TODO: flyweight pattern
    std::unique_ptr<SDLTexture> player_texture_;
    std::unique_ptr<SDLTexture> bullet_texture_;
    std::unique_ptr<SDLTexture> enemy_texture_;
    std::unique_ptr<SDLTexture> alien_bullet_texture_;
    std::unique_ptr<Player> player_;
    std::list<Entity> entities_;
    std::list<Entity> enemies_;
    int enemySpawnTimer_{0};

    // SDL_Point food;
    bool running_;

    std::random_device dev_;
    std::mt19937 eng_;
    std::uniform_int_distribution<int> random_y_;
    std::uniform_int_distribution<int> random_dx_;
    std::uniform_int_distribution<int> random_dy_;
    std::uniform_int_distribution<int> random_timer_;
    std::uniform_int_distribution<int> random_alien_bullet_;

    // int score{0};

    // void PlaceFood();
    bool BulletHitFighter(Entity &b);
    void CalcSlope(int x1, int y1, int x2, int y2, float *dx, float *dy);
    bool Collision(int x1, int y1, int w1, int h1,
                   int x2, int y2, int w2, int h2);
    void FireAlienBullet(Entity &e);
    void FireBullet();
    void SpawnEnemies();
};

#endif