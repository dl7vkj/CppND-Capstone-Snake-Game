#include "game_components.h"

#include <vector>
#include <random>

#include "SDL.h"

#include "config.h"
#include "utility.h"
#include "game.h"
#include "game_object.h"


void PlayerInputComponent::Update(GameObject &obj, const uint8_t *keyboard_state) {
    obj.dx = 0.0f;
    obj.dy = 0.0f;
    if (keyboard_state[SDL_SCANCODE_UP]) {
        obj.dy = -4.0f;
    }
    if (keyboard_state[SDL_SCANCODE_DOWN]) {
        obj.dy = 4.0f;
    }
    if (keyboard_state[SDL_SCANCODE_LEFT]) {
        obj.dx = -4.0f;
    }
    if (keyboard_state[SDL_SCANCODE_RIGHT]) {
        obj.dx = 4.0f;
    }
    if (keyboard_state[SDL_SCANCODE_LCTRL]) {
        obj.fireBullet = true;
    }
}

void PlayerPhysicsComponent::Update(GameObject &obj, Game &game) {
    // Move the object
    obj.x += obj.dx;
    obj.y += obj.dy;
    // Get the screen size
    int screen_w = game.GetRendererHandle().GetScreenWidth();
    int screen_h = game.GetRendererHandle().GetScreenHeight();
    int max_x = screen_w - obj.w;
    int max_y = screen_h - obj.h;

    // Don't move outside the screen
    if (obj.x < 0) {
        obj.x = 0;
    } else if (obj.x > max_x) {
        obj.x = max_x;
    }
    if (obj.y < 0) {
        obj.y = 0;
    } else if (obj.y > max_y) {
        obj.y = max_y;
    }

    if (--reload <= 0 && obj.fireBullet) {
        reload = kReloadTime;
        obj.fireBullet = false;
        float x = obj.x + obj.w;
        float y = obj.y + (obj.h / 2.0f);
        game.FireBullet(x, y, Config::kBulletSpeed, 0.0f,
                        GameObject::Side::kPlayer);
    }
};


void AlienPhysicsComponent::Update(class GameObject &obj, class Game &game) {
    // Move the object
    obj.x += obj.dx;
    obj.y += obj.dy;
    // Alien killed
    if (obj.health <= 0) {
        obj.isAlive = false;
        return;
    }
    // Alien leave playground...
    if (obj.x < -obj.w) {
        obj.isAlive = false;
        return;
    }
    // Alien bounce off
    if (obj.y <= 0) {
        obj.dy = fabsf(obj.dy);
    } else if (obj.y >= game.GetRendererHandle().GetScreenHeight() - obj.h) {
        obj.dy = -fabsf(obj.dy);
    }
    // Alien shoot
    if (--reloadTime_ <= 0) {
        FireBullet(obj, game);
        reloadTime_ = game.GetRandomAlienBulletReloadTime();
    }
};

void AlienPhysicsComponent::FireBullet(class GameObject &obj, class Game &game) {
    float x = obj.x;
    float y = obj.y;
    x += (obj.w / 2);
    y += (obj.h / 2);

    // Set bullet velocity
    SDL_FPoint slope =  Utility::CalcSlope({x, y}, game.GetPlayerRect());
    slope.x *= Config::kAlienBulletSpeed;
    slope.y *= Config::kAlienBulletSpeed;
    game.FireBullet(x, y, slope.x, slope.y, GameObject::Side::kAlien);
}

void BulletPhysicsComponent::Update(GameObject &obj, Game &game) {
    // Move the object
    obj.x += obj.dx;
    obj.y += obj.dy;
    // Get the screen size
    int screen_w = game.GetRendererHandle().GetScreenWidth();
    int screen_h = game.GetRendererHandle().GetScreenHeight();

    if (obj.health <= 0) {
        obj.isAlive = false;
        return;
    }
    // Bullets die when they leave the screen
    if (obj.x > game.GetRendererHandle().GetScreenWidth()) {
        obj.isAlive = false;
    } else if (obj.x < -obj.w) {
        obj.isAlive = false;
    }
    if (obj.y > game.GetRendererHandle().GetScreenHeight()) {
        obj.isAlive = false;
    } else if (obj.y < -obj.h) {
        obj.isAlive = false;
    }
};


StarPhysicsComponent::StarPhysicsComponent(Game &game)
: screenWidth_(game.GetRendererHandle().GetScreenWidth()) {
    // Setup random generator
    std::random_device dev;
    std::mt19937 eng{dev()};
    std::uniform_int_distribution<int> dist{0, std::numeric_limits<int>::max()};

    int screenHeight = game.GetRendererHandle().GetScreenHeight();
    Star star;
    // Create 500 stars
    for (int i = 0; i < 500; i++) {
        star.x = dist(eng) % screenWidth_;
        star.y = dist(eng) % screenHeight;
        star.dx = (10 + dist(eng) % 20)*-0.1f;
        stars_.emplace_back(star);
    }
}

void StarPhysicsComponent::Update(GameObject &obj, Game &game) {
    for (auto &star: stars_) {
        star.x += star.dx;
        // Wrap
        if (star.x < 0) {
            star.x += screenWidth_;
        }
    }
};

// RUBRIC: Class constructors utilize member initialization lists.
StarGraphicsComponent::StarGraphicsComponent(StarPhysicsComponent *starPhyC_)
: starPhyC_(starPhyC_) {}

void StarGraphicsComponent::Update(class GameObject &obj, class Renderer &renderer) {
    std::vector<StarPhysicsComponent::Star> const &stars = starPhyC_->GetStars();
    // TODO: Add to constructor
    SDL_Renderer *sdl_renderer = renderer.GetSDLRendererHandle();
    if (sdl_renderer == nullptr)
        return;
    for (auto &star: stars) {
        int c = star.dx;
        c *= -84;
        SDL_SetRenderDrawColor(sdl_renderer, c, c, c, 255);
        int x = star.x;
        int y = star.y;
        SDL_RenderDrawLine(sdl_renderer, x, y, x + 3, y);
    }
}
