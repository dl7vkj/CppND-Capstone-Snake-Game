#ifndef CONFIG_H
#define CONFIG_H

#include <cstddef>
#include <string>

namespace Config {
  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{640};
  constexpr std::size_t kScreenHeight{640};
  constexpr std::size_t kGridWidth{32};
  constexpr std::size_t kGridHeight{32};
  const std::string kPlayerImage{"../gfx/player.png"};
}

#endif // CONFIG_H
