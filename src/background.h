#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <vector>
#include <memory>
#include <functional>
#include <random>
#include <limits>

#include "SDL.h"

#include "star.h"


class Background {
public:

    Background() {
        std::random_device dev;
        std::mt19937 eng{dev()};
        std::uniform_int_distribution<int> dist{0, std::numeric_limits<int>::max()};



        for (int i = 0; i < 500; i++) {
            // int x = dist(eng) % screenWidth_;
            // int y = dist(eng) % screenHeight_;
            float speed = (10 + dist(eng) % 80)*0.1f; // 1.0 - 9.0
            auto star = std::make_unique<Star>(nullptr, speed);
            star->SetPosition(x, y);
            stars_.emplace_back(std::move(star));
        }
    }

    void Draw() {

    }

    void Update() {

    }

private:
    std::vector<std::unique_ptr<Star>> stars_;
};

#endif // BACKGROUND_H
