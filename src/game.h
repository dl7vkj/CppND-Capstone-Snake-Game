#ifndef GAME_H
#define GAME_H

#include <random>
#include <vector>

#include "SDL.h"

#include "renderer.h"
#include "game_object.h"


class Game {
public:
    enum State{kPlay, kRespawn, kPause};

    Game();

    void Run();

    Renderer &GetRenderer() { return renderer_; }

    void AddGameObject(std::unique_ptr<GameObject> obj) {
        pendingObjs_.emplace_back(std::move(obj));
    }

    void AddBullet(std::unique_ptr<GameObject> obj) {
        bullets_.emplace_back(std::move(obj));
    }

    void Clear();

    SDL_Rect GetPlayerRect() {
        auto &player = objs_[0];
        SDL_Rect retval;
        retval.x = player->x;
        retval.y = player->y;
        retval.w = player->w;
        retval.h = player->h;
        return retval;
    }

    void FireBullet(float x, float y, float dx, float dy,
                    GameObject::Side side);

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

    void DetectBulletCollision(GameObject *bullet);
    void SpawnAliens();
    void CreateBackgound();

    Renderer renderer_;
    std::vector<std::unique_ptr<GameObject>> objs_{};
    std::vector<std::unique_ptr<GameObject>> pendingObjs_{};
    std::vector<std::unique_ptr<GameObject>> bullets_{};

    int alienSpawnTimer_{60};
    bool running_{true};
    int remainingLives_{kRemainingLives};
    int score_{0};
    int respawnTimer_{kRespawnTime};
    State state_{kPlay};
    std::unique_ptr<GameObject> background_;

    // TODO: Refactor
    std::random_device dev_;
    std::mt19937 eng_;
    std::uniform_int_distribution<int> random_y_;
    std::uniform_real_distribution<float> random_dx_;
    std::uniform_real_distribution<float> random_dy_;
    std::uniform_int_distribution<int> random_timer_;
    std::uniform_int_distribution<int> random_alien_bullet_;
};

#endif