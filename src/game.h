#ifndef GAME_H
#define GAME_H

#include <random>
#include <vector>

#include "SDL2/SDL.h"

#include "renderer.h"
#include "game_object.h"


class Game {
public:
    enum State{kPlay, kRespawn, kPause};

    using UPtrGameObject = std::unique_ptr<GameObject>;
    using VecUPtrGameObject = std::vector<UPtrGameObject>;

    Game();

    Renderer &GetRendererHandle();
    // Return player position and size
    SDL_Rect GetPlayerRect();
    int GetRandomAlienBulletReloadTime();

    // Game loop
    void Run();
    // Remove GameObjects, except for player and background
    void Clear();
    // Fire a bullet at position (x, y) with velocity (dx, dy) and side side.
    void FireBullet(float x, float y, float dx, float dy,
                    GameObject::Side side);

    // int GetScore() const;
    // int GetSize() const;

private:
    static constexpr int kRespawnTime{180};
    static constexpr int kRemainingLives{2};
    static constexpr int kPlayerHealth{3};

    Renderer renderer_;
    VecUPtrGameObject objs_{};        // GameObjects
    VecUPtrGameObject pendingObjs_{}; // Pending Objects
    VecUPtrGameObject bullets_{};     // Bullets
    UPtrGameObject background_;

    int alienSpawnTimer_{60};
    bool running_{true};
    int remainingLives_{kRemainingLives};
    int score_{0};
    int respawnTimer_{kRespawnTime};
    State state_{kPlay};

    // TODO: Refactor
    std::random_device dev_;
    std::mt19937 eng_;
    std::uniform_int_distribution<int> random_y_;
    std::uniform_real_distribution<float> random_dx_;
    std::uniform_real_distribution<float> random_dy_;
    std::uniform_int_distribution<int> random_timer_;
    std::uniform_int_distribution<int> random_alien_bullet_;

    void Input();
    void Update();
    void Output();

    void DetectBulletCollision(GameObject *bullet);
    void SpawnAliens();
    void CreateBackgound();

    void AddBullet(UPtrGameObject obj);
    void AddGameObject(UPtrGameObject obj);
};

#endif // GAME_H
