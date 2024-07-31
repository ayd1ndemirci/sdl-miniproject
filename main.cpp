#include <iostream>
#include <SDL2/SDL.h>

const int WIDTH = 800, HEIGHT = 600;

void handleKeyDown(const Uint8* state, int &boxX, int &boxY, int speed) {
    if (state[SDL_SCANCODE_A] || state[SDL_SCANCODE_LEFT]) {
        boxX -= speed;
    }
    if (state[SDL_SCANCODE_S] || state[SDL_SCANCODE_DOWN]) {
        boxY += speed;
    }
    if (state[SDL_SCANCODE_D] || state[SDL_SCANCODE_RIGHT]) {
        boxX += speed;
    }
    if (state[SDL_SCANCODE_W] || state[SDL_SCANCODE_UP]) {
        boxY -= speed;
    }
}

int main(int argc, char *argv[])
{
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window *window = SDL_CreateWindow("Game Project", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);

    if (NULL == window)
    {
        std::cout << "Pencere olusturulamadi: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);

    SDL_Event event;

    int boxX = WIDTH / 2;
    int boxY = HEIGHT / 2;
    int boxSize = 50;
    int speed = 5;
    
    bool running = true;
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (SDL_QUIT == event.type) {
               running = false;
            }
        }

        const Uint8 *state = SDL_GetKeyboardState(NULL);
        handleKeyDown(state, boxX, boxY, speed);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // siyah arka plan
        SDL_RenderClear(renderer);
        SDL_Rect box = {boxX, boxY, boxSize, boxSize};
        SDL_SetRenderDrawColor(renderer, 0, 0, 128, 255); // lacivert kutu
        SDL_RenderFillRect(renderer, &box);
        SDL_RenderPresent(renderer);
        SDL_Delay(10);
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}
