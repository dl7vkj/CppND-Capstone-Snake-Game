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
#include "actor.h"
#include "bullet_actor.h"


class Game {
public:
    enum State{kPlay, kRespawn, kPause};
    // Game(Renderer &renderer);
    // void Run(Controller &controller,
    //         std::size_t target_frame_duration);
    Game();

    void Run();

    Renderer *GetRenderer() { return renderer_.get(); }
    void AddActor(std::unique_ptr<Actor> actor) {
        pendingActors_.emplace_back(std::move(actor));
    }
    void AddBullet(std::unique_ptr<BulletActor> bullet) {
        pendingBullets_.emplace_back(std::move(bullet));
    }
    SDL_Rect GetPlayerRect() { return actors_[0]->GetRect(); }
    int GetRandomAlienBulletReloadTime() { return random_alien_bullet_(eng_); }
    // int GetScore() const;
    // int GetSize() const;

private:
    static constexpr int kRespawnTime{180};
    static constexpr int kRemainingLives{2};
    static constexpr int kPlayerHealth{3};

    void Input();
    void Update();
    void Output();

    void DetectBulletCollision(BulletActor *bullet);
    void SpawnAliens();

    std::unique_ptr<Renderer> renderer_;
    std::vector<std::unique_ptr<Actor>> actors_{};
    std::vector<std::unique_ptr<Actor>> pendingActors_{};
    std::vector<std::unique_ptr<BulletActor>> bullets_{};
    std::vector<std::unique_ptr<BulletActor>> pendingBullets_{};

    int alienSpawnTimer_{60};
    bool running_{true};
    int remainingLives_{kRemainingLives};
    int score_{0};
    int respawnTimer_{kRespawnTime};
    State state_{kPlay};

    std::random_device dev_;
    std::mt19937 eng_;
    std::uniform_int_distribution<int> random_y_;
    std::uniform_real_distribution<float> random_dx_;
    std::uniform_real_distribution<float> random_dy_;
    std::uniform_int_distribution<int> random_timer_;
    std::uniform_int_distribution<int> random_alien_bullet_;

#if 0
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
#endif
};

#endif