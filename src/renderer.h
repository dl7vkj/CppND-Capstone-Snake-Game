#ifndef RENDERER_H
#define RENDERER_H

#include <list>
#include <string>

#include "SDL.h"

#include "player.h"
#include "entity.h"
#include "sdl_texture.h"

class Renderer {
 public:
  Renderer(const std::size_t screen_width, const std::size_t screen_height);
  ~Renderer();

  void Render(std::list<Player> &players, std::list<Entity> &entities);
  void UpdateWindowTitle(int fps);

  // SDLTexture &MakeTexture(std::string filename) {
  //   SDLTexture texture(filename, *sdl_renderer);
  //   textures_.emplace_back(std::move(texture));
  //   return textures_.back();
  // }

  std::size_t GetWidth() const { return screenWidth_; }
  std::size_t GetHeight() const { return screenHeight_; }
  SDL_Renderer *GetSDLRenderer() { return sdl_renderer; }

 private:
  SDL_Window *sdl_window;
  SDL_Renderer *sdl_renderer;
  // std::vector<SDLTexture> textures_;

  const std::size_t screenWidth_;
  const std::size_t screenHeight_;
};

#endif