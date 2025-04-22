#include "pipes.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <SDL_image.h>
#include "textures.h"
const int SCREEN_WIDTH = 800;   
const int SCREEN_HEIGHT = 600;
SDL_Texture* pipeTexture = nullptr;

void InitPipes(std::vector<SDL_Rect>& pipes, SDL_Renderer* renderer) {
    CleanupPipes();
    pipeTexture = LoadTexture("pipe.png", renderer);
    if (!pipeTexture) {
        std::cout << "Khong tai duoc anh pipe.png! " << SDL_GetError() << std::endl;
        return;
    }

    std::srand(std::time(0));

    int numPipes = 4; 

    for (int i = 0; i < numPipes; i++) {
        int pipeHeight = std::rand() % (SCREEN_HEIGHT - PIPE_GAP - 50);
        pipes.push_back({ SCREEN_WIDTH + i * (PIPE_WIDTH + 150), pipeHeight - PIPE_HEIGHT, PIPE_WIDTH, PIPE_HEIGHT });
        pipes.push_back({ SCREEN_WIDTH + i * (PIPE_WIDTH + 150), pipeHeight + PIPE_GAP, PIPE_WIDTH, PIPE_HEIGHT });
    }
}


void UpdatePipes(std::vector<SDL_Rect>& pipes) {
    for (auto& pipe : pipes) {
        pipe.x -= PIPE_SPEED;
    }

    // Kiểm tra xem ống đầu tiên có ra khỏi màn hình không
    if (pipes.front().x + PIPE_WIDTH < 0) {
        pipes.erase(pipes.begin(), pipes.begin() + 2); 

        int pipeHeight = std::rand() % (SCREEN_HEIGHT - PIPE_GAP - 100) + 50;
        int lastPipeX = pipes[pipes.size() - 2].x; 

        pipes.push_back({ lastPipeX + PIPE_WIDTH + 220, 0, PIPE_WIDTH, pipeHeight }); 
        pipes.push_back({ lastPipeX + PIPE_WIDTH + 220, pipeHeight + PIPE_GAP, PIPE_WIDTH, SCREEN_HEIGHT - (pipeHeight + PIPE_GAP) });
       
    }
}


void RenderPipes(SDL_Renderer* renderer, const std::vector<SDL_Rect>& pipes) {
    for (size_t i = 0; i < pipes.size(); i++) {
        SDL_RenderCopy(renderer, pipeTexture, NULL, &pipes[i]);
    }
}

void CleanupPipes() {
    if (pipeTexture) {
        SDL_DestroyTexture(pipeTexture);
        pipeTexture = nullptr;
    }
}