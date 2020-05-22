#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <list>

#include "SDL.h"

#include "player.h"


class Controller {
public:
    void HandleInput(bool &running,
                     std::list<Player> &players,
                     std::list<Entity> &entities);

protected:
    void KeyUp(SDL_KeyboardEvent &event,
               std::list<Player> &players,
                std::list<Entity> &entities);
    void KeyDown(SDL_KeyboardEvent &event,
                 std::list<Player> &players,
                 std::list<Entity> &entities);

private:
//   void ChangeDirection(Snake &snake, Snake::Direction input,
//                        Snake::Direction opposite) const;
};

#endif // CONTROLLER_H
