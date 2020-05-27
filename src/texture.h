#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include <memory>

#include "SDL.h"



class Texture {
public:
    Texture (std::string const &filename, SDL_Renderer *sdl_renderer);

    // RUBRIC: Rule of five
    ~Texture();
    Texture(const Texture &source);            // Copy contructor
    Texture &operator=(const Texture &source); // Copy assignment operator
    Texture(Texture &&source);                 // Move constructor
    Texture &operator=(Texture &&source);      // Move assignment operator

    // Returns the SDL texture
    SDL_Texture *GetSDLTexture() const;
    // Get textures height
    int GetHeight() const;
    // Get textures width
    int GetWidth() const;

    // Draw(blit) texture on SDL renderer at position (x, y).
    void Blit(int x, int y) const;

private:
    std::string filename_;
    SDL_Renderer *renderer_;
    SDL_Texture *texture_;
    int width_{0};
    int height_{0};
};

#endif // TEXTURE_H
