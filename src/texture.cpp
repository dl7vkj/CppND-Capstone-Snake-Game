#include "texture.h"

#include <iostream>

#include "SDL_image.h"


Texture::Texture (std::string const &filename, SDL_Renderer *sdl_renderer)
: filename_(filename), renderer_(sdl_renderer)
{
    if (renderer_ == nullptr) {
        SDL_LogMessage(SDL_LOG_CATEGORY_RENDER, SDL_LOG_PRIORITY_CRITICAL,
                    "Texture failed: sdl_renderer points to nullptr");
        return;
    }
    SDL_LogMessage(SDL_LOG_CATEGORY_RENDER, SDL_LOG_PRIORITY_INFO,
                    "Loading texture %s", filename_.c_str());
    // Load image from filesystem
    texture_ = IMG_LoadTexture(renderer_, filename_.c_str());
    if (texture_ == nullptr) {
        SDL_LogMessage(SDL_LOG_CATEGORY_RENDER, SDL_LOG_PRIORITY_CRITICAL,
                    "IMG_LoadTexture failed: %s", filename_.c_str());
        return;
    }
    // Get height and width of texture
    if (SDL_QueryTexture(texture_, NULL, NULL, &width_, &height_))
    {
        SDL_LogMessage(SDL_LOG_CATEGORY_RENDER, SDL_LOG_PRIORITY_CRITICAL,
                    "SDL_QueryTexture failed: %s", SDL_GetError());
        if (texture_ != nullptr) {
            SDL_DestroyTexture(texture_);
            texture_ == nullptr;
        }
    }
}

Texture::~Texture() {
    if (texture_ != nullptr) {
        SDL_DestroyTexture(texture_);
    }
}

// copy contructor
Texture::Texture(const Texture &source)
{
    std::cout << "Texture Copy Constructor\n";
    filename_ = source.filename_;
    renderer_ = source.renderer_;
    width_ = source.width_;
    height_ = source.height_;

    if (renderer_ != nullptr) {
        // Load image from filesystem
        texture_ = IMG_LoadTexture(renderer_, filename_.c_str());
    }
}

// copy assignment operator
Texture &Texture::operator=(const Texture &source)
{
    std::cout << "Texture Copy Assignment Operator\n";
    if (this == &source)
        return *this;

    if(texture_ != nullptr)
    {
        SDL_DestroyTexture(texture_);
    }

    filename_ = source.filename_;
    renderer_ = source.renderer_;
    width_ = source.width_;
    height_ = source.height_;

    if (renderer_ != nullptr) {
        // Load image from filesystem
        texture_ = IMG_LoadTexture(renderer_, filename_.c_str());
    }

    return *this;
}

// move constructor
Texture::Texture(Texture &&source)
{
    std::cout << "Texture Move Constructor\n";
    // copy data from source
    filename_ = source.filename_;
    renderer_ = source.renderer_;
    texture_ = source.texture_;
    width_ = source.width_;
    height_ = source.height_;

    // invalidate source data handles
    renderer_ = nullptr;
    texture_ = nullptr;
}

// move assignment operator
Texture &Texture::operator=(Texture &&source)
{
    std::cout << "Texture Move Assignment Operator\n";
    if (this == &source)
        return *this;

    if(texture_ != nullptr)
    {
        SDL_DestroyTexture(texture_);
    }

    // copy data from source
    filename_ = source.filename_;
    renderer_ = source.renderer_;
    texture_ = source.texture_;
    width_ = source.width_;
    height_ = source.height_;

    // invalidate source data handles
    renderer_ = nullptr;
    texture_ = nullptr;

    return *this;
}


SDL_Texture *Texture::GetSDLTexture() const  { return texture_; }

int Texture::GetWidth() const { return width_; }
int Texture::GetHeight() const { return height_; }

void Texture::Blit(int x, int y) const {
    if (nullptr == texture_) {
        return;
    }
    SDL_Rect dest;

    dest.x = x;
    dest.y = y;
    dest.w = width_;
    dest.h = height_;

    // Draw image on SDL renderer.
    SDL_RenderCopy(renderer_, texture_, NULL, &dest);
}
