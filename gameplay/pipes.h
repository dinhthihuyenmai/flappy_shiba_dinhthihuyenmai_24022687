#ifndef PIPES_H
#define PIPES_H

#include <SDL.h>
#include <vector>

const int PIPE_WIDTH = 100;
const int PIPE_HEIGHT = 300;
const int PIPE_GAP = 250;
const int PIPE_SPEED = 2;

void InitPipes(std::vector<SDL_Rect>& pipes, SDL_Renderer* renderer);
void UpdatePipes(std::vector<SDL_Rect>& pipes);
void RenderPipes(SDL_Renderer* renderer, const std::vector<SDL_Rect>& pipes);
void CleanupPipes();

#endif