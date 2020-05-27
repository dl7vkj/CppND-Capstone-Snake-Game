#ifndef UTILITY_H
#define UTILITY_H

#include <cmath>

#include "SDL2/SDL.h"


namespace Utility {

// RUBRIC: Templates generalize functions in the project.
template <typename T>
T Max(const T &a, const T &b) {
    return a < b ? b : a;
}

// RUBRIC: The project makes use of references in function declarations.
// Calculate the slope from position pos to center of target
SDL_FPoint CalcSlope(SDL_FPoint const &pos, SDL_Rect const &target);

}

#endif // UTILITY_H
