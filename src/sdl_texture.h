#ifndef SDL_TEXTURE_H
#define SDL_TEXTURE_H

#include <string>
#include <memory>

#include "SDL.h"
#include "SDL_image.h"


class SDLTexture {
public:
    SDLTexture (std::string &filename, SDL_Renderer &sdl_renderer)
    : renderer_(sdl_renderer)
    {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO,
                       "Loading %s", filename.c_str());
        // First get raw pointer to SDL_Texture.
        texture_ = IMG_LoadTexture(&sdl_renderer,
                                               filename.c_str());
        // // If success, store raw pointer into smart pointer.
        // if (nullptr != texture)
        //     texture_ = std::unique_ptr<SDL_Texture>(texture);
        // TODO: Error handling
    }

    SDL_Texture *GetTexture ()  { return texture_; }

    void Blit (int x, int y) {
        SDL_Rect dest;

        dest.x = x;
        dest.y = y;
        //
        SDL_QueryTexture(texture_, NULL, NULL, &dest.w, &dest.h);
        // Draw image on SDL renderer.
        SDL_RenderCopy(&renderer_, texture_, NULL, &dest);
    }

private:
    SDL_Renderer &renderer_;
    SDL_Texture *texture_;
};

#endif // SDL_TEXTURE_H
