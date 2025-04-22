#include "collision.h"

bool CheckCollision(const SDL_Rect& a, const std::vector<SDL_Rect>& pipes) {
    for (const auto& pipe : pipes) {
        if (SDL_HasIntersection(&a, &pipe)) {
            return true;
        }
    }
    return false;
}
