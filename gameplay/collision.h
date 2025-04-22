#pragma once
#include <SDL.h>
#include <vector>

bool CheckCollision(const SDL_Rect& a, const std::vector<SDL_Rect>& pipes);
