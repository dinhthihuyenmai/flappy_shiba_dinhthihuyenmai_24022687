 #include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "textures.h"
#include "pipes.h"  
#include "collision.h"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int GRAVITY = 1;
const int FLAP_STRENGTH = -10;

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0 || !(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        std::cout << "SDL khong the khoi tao! SDL_Error: " << SDL_GetError() << std::endl;
        return -1;
    }

    SDL_Window* window = SDL_CreateWindow("Flappy Shiba", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    SDL_Texture* shibaTexture = LoadTexture("shiba.png", renderer);
    if (!shibaTexture) {
        std::cout << "Khong the tai hinh anh Shiba!" << std::endl;
        return -1;
    }

    SDL_Texture* gameOverTexture = LoadTexture("gameOver.png", renderer);
    if (!gameOverTexture) {
        std::cout << "Khong the tai gameOver.png!" << std::endl;
        return -1;
    }

    // Khởi tạo các ống
    std::vector<SDL_Rect> pipes;
    InitPipes(pipes, renderer);

    SDL_Rect shibaRect = { 100, SCREEN_HEIGHT / 2, 50, 35 };
    int velocityY = 0;
    bool running = true;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
            if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE) {
                velocityY = FLAP_STRENGTH;
            }
        }

        // Cập nhật vị trí Shiba
        velocityY += GRAVITY;
        shibaRect.y += velocityY;

        // Kiểm tra va chạm với đáy màn hình
        if (shibaRect.y + shibaRect.h > SCREEN_HEIGHT) {
            std::cout << "Game Over! Shiba cham dat.\n";
            running = false;
        }

        // Cập nhật vị trí các ống
        UpdatePipes(pipes);

        // Kiểm tra va chạm với ống nước
        if (CheckCollision(shibaRect, pipes)) {
            std::cout << "Game Over! Shiba dam vao ong nuoc.\n";
            running = false;
        }

        // Xóa màn hình
        SDL_SetRenderDrawColor(renderer, 0, 191, 255, 255);
        SDL_RenderClear(renderer);

        // Vẽ Shiba
        SDL_RenderCopy(renderer, shibaTexture, NULL, &shibaRect);

        // Vẽ các ống nước
        RenderPipes(renderer, pipes);

        SDL_RenderPresent(renderer);

        SDL_Delay(16);
    }

    // Hiển thị màn hình Game Over
    SDL_Rect gameOverRect = { SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 - 50, 200, 100 };
    SDL_RenderCopy(renderer, gameOverTexture, NULL, &gameOverRect);
    SDL_RenderPresent(renderer);
    // Chờ người chơi nhấn phím để thoát
    bool waitForExit = true;
    while (waitForExit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT ||
                (event.type == SDL_KEYDOWN)) {
                waitForExit = false;
            }
        }
        SDL_Delay(10);
    }

    // Giải phóng bộ nhớ
    SDL_DestroyTexture(shibaTexture);
    SDL_DestroyTexture(gameOverTexture);
    CleanupPipes();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();

    return 0;
}
