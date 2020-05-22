#ifndef GAME_H
#define GAME_H

// #include <random>
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
    std::list<Player> players_;
    std::list<Entity> entities_;

    // SDL_Point food;

    // std::random_device dev;
    // std::mt19937 engine;
    // std::uniform_int_distribution<int> random_w;
    // std::uniform_int_distribution<int> random_h;

    // int score{0};

    // void PlaceFood();
    void FireBullet();
    void Update();
    std::unique_ptr<SDLTexture> player_texture_;
    std::unique_ptr<SDLTexture> bullet_texture_;
};

#endif