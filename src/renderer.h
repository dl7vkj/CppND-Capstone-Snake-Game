#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include <string>
#include "SDL.h"
#include "player.h"
#include "sdl_texture.h"

class Renderer {
 public:
  Renderer(const std::size_t screen_width, const std::size_t screen_height);
  ~Renderer();

  void Render(Player const &player);
  void UpdateWindowTitle(int fps);

  SDLTexture &MakeTexture(std::string filename) {
    SDLTexture texture(filename, *sdl_renderer);
    textures_.emplace_back(std::move(texture));
    return textures_.back();
  }

 private:
  SDL_Window *sdl_window;
  SDL_Renderer *sdl_renderer;
  std::vector<SDLTexture> textures_;

  const std::size_t screen_width;
  const std::size_t screen_height;
};

#endif