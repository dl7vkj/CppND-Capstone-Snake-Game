#ifndef UTILITY_H
#define UTILITY_H

#include <cmath>

#include "SDL.h"


namespace Utility {

template <typename T>
T Max(const T &a, const T &b) {
    return a < b ? b : a;
}

// Calculate the slope from position pos to center of target
SDL_FPoint CalcSlope(SDL_FPoint pos, SDL_Rect target);

}

#endif // UTILITY_H
