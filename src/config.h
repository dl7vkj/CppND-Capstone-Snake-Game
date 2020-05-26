#ifndef CONFIG_H
#define CONFIG_H

#include <cstddef>
#include <string>

namespace Config {
  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{1280};
  constexpr std::size_t kScreenHeight{720};
  constexpr int kBulletSpeed{16};
  constexpr int kAlienBulletSpeed{10};
  constexpr int kPlayerSpeed{5};
  // constexpr std::size_t kGridWidth{32};
  // constexpr std::size_t kGridHeight{32};
  const std::string kPlayerImage{"../gfx/player.png"};
  const std::string kEnemyImage{"../gfx/enemy.png"};
  const std::string kBulletImage{"../gfx/playerBullet.png"};
  const std::string kAlienBulletImage{"../gfx/alienBullet.png"};
}

#endif // CONFIG_H
