#include <SDL3/SDL.h>

#include <iostream>

int main(int argc, char* argv[]) {
  const int PIXEL_SIZE = 12;
  const int WINDOW_WIDTH = 100;
  const int WINDOW_HEIGHT = 100;

  void drawObjectAt(SDL_Renderer* renderer, int logicalX, int logicalY) {
    SDL_FRect rect = {static_cast<float>(logicalX * PIXEL_SIZE),
                      static_cast<float>(logicalY * PIXEL_SIZE), PIXEL_SIZE,
                      PIXEL_SIZE};
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);  // Red
    SDL_RenderFillRect(renderer, &rect);
  }

  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError()
              << std::endl;
    return -1;
  }

  SDL_Window* window =
      SDL_CreateWindow("SDL Window", WINDOW_WIDTH * PIXEL_SIZE,
                       WINDOW_HEIGHT * PIXEL_SIZE, SDL_WINDOW_RESIZABLE);
  if (window == nullptr) {
    std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError()
              << std::endl;
    SDL_Quit();
    return -1;
  }

  SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL);
  if (renderer == nullptr) {
    std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError()
              << std::endl;
    SDL_DestroyWindow(window);
    SDL_Quit();
    return -1;
  }

  SDL_Event event;

  // Main loop
  bool quit = false;
  while (!quit) {
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_EVENT_QUIT) {
        quit = true;
      }
    }

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    drawObjectAt(renderer, 50, 50);

    SDL_RenderPresent(renderer);

    SDL_Delay(100);
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
