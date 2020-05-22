#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "SDL.h"
#include "player.h"


class Controller {
public:
    void HandleInput(Player &player, bool &running) const;

protected:
    void KeyUp(Player &player, SDL_KeyboardEvent &event) const;
    void KeyDown(Player &player, SDL_KeyboardEvent &event) const;

private:
//   void ChangeDirection(Snake &snake, Snake::Direction input,
//                        Snake::Direction opposite) const;
};

#endif // CONTROLLER_H
