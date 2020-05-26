#ifndef STAR_PHYSICS_COMPONENT_H
#define STAR_PHYSICS_COMPONENT_H

#include <vector>
#include <random>
#include <limits>

#include "SDL.h"

#include "physics_component.h"
#include "game.h"
#include "game_object.h"

// TODO: Comment
class StarPhysicsComponent : public PhysicsComponent {
public:

    struct Star {
        float x;
        float y;
        float dx;
    };

    StarPhysicsComponent(Game &game)
    : screenWidth_(game.GetRenderer().GetScreenWidth()) {
        // Setup random generator
        std::random_device dev;
        std::mt19937 eng{dev()};
        std::uniform_int_distribution<int> dist{0, std::numeric_limits<int>::max()};

        int screenHeight = game.GetRenderer().GetScreenHeight();
        Star star;
        // Create 500 stars
        for (int i = 0; i < 500; i++) {
            star.x = dist(eng) % screenWidth_;
            star.y = dist(eng) % screenHeight;
            star.dx = (10 + dist(eng) % 20)*-0.1f;
            stars_.emplace_back(star);
        }
    }

    void Update(GameObject &obj, Game &game) override {
        for (auto &star: stars_) {
            star.x += star.dx;
            // Wrap
            if (star.x < 0) {
                star.x += screenWidth_;
            }
        }
    };

    std::vector<Star> &GetStars() { return stars_; }

private:
    std::vector<Star> stars_{};
    int screenWidth_;
};


#endif // STAR_PHYSICS_COMPONENT_H
