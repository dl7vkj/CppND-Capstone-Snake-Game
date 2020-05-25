#include "utility.h"

namespace Utility {

SDL_FPoint CalcSlope(SDL_FPoint pos, SDL_Rect target)
{
    SDL_FPoint retval;

    float x1{pos.x};
    float y1{pos.y};
    float x2{target.x + target.w * 0.5f};
    float y2{target.y + target.h * 0.5f};

    float steps{Max(fabsf(x1 - x2), fabsf(y1 - y2))};

    if (fabsf(steps) < 1.0f)
    {
        retval.x = 0.0f;
        retval.y = 0.0f;
    } else {
        retval.x = (x2 - x1);
        retval.x /= steps;
        retval.y = (y2 - y1);
        retval.y /= steps;
    }
    return retval;
}

}
