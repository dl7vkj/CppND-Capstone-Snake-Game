#ifndef PLAYER_H
#define PLAYER_H

#include "sdl_texture.h"


class Player {
public:
    Player(SDLTexture &texture) : texture_(texture) {}
    void SetPosition(int x, int y) {
        x_ = x;
        y_ = y;
    }
    void Render() const {texture_.Blit(x_, y_); }
private:
    int x_{0};
    int y_{0};
    SDLTexture &texture_;
};


#endif // PLAYER_H
