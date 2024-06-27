#include "gamedisplay.h"

#include <SDL3/SDL.h>

#include <cstddef>
#include <cstdint>
#include <deque>
#include <iostream>
#include <utility>

#include "gamestatus.h"

namespace gamedisplay {

void drawObjectAt(SDL_Renderer* sdl_renderer,
                  std::deque<std::pair<int, int>> obj, int pixel_size) {
  for (auto& element : obj) {
    auto logicalX = element.first;
    auto logicalY = element.second;

    SDL_FRect rect = {static_cast<float>(logicalX * pixel_size),
                      static_cast<float>(logicalY * pixel_size),
                      static_cast<float>(pixel_size),
                      static_cast<float>(pixel_size)};
    SDL_SetRenderDrawColor(sdl_renderer, 255, 0, 0, 255);  // Red
    SDL_RenderFillRect(sdl_renderer, &rect);
  }
}

Game::Game(int width, int height, int pixel_size) noexcept
    : window_width_(width),
      window_height_(height),
      pixel_size_(pixel_size),
      game_window_(width, height, pixel_size),
      game_renderer_(game_window_),
      snake_(width, height) {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "Renderer could not be created! SDL_Error:" << SDL_GetError()
              << "\n";
    initialized_ = false;
    return;
  }

  sdl_window_ = game_window_.getWindow();
  sdl_renderer_ = game_renderer_.getRenderer();
}

void Game::render() {
  SDL_SetRenderDrawColor(sdl_renderer_, 255, 255, 255, 255);
  SDL_RenderClear(sdl_renderer_);
  drawObjectAt(sdl_renderer_, snake_.getBody().deque(), pixel_size_);
  SDL_RenderPresent(sdl_renderer_);
  SDL_Delay(1000);
}

void Game::handleEvents(SDL_Event& event) {
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
      case SDL_EVENT_QUIT:
        is_running_ = false;
        break;
      case SDL_EVENT_KEY_DOWN:
        switch ((event.key.keysym.scancode)) {
          case SDL_SCANCODE_UP:
            //std::cout<<"new direction: UP \n";
            snake_.newDirection(gamestatus::Direction::UP);
        }
      default:
        break;
    }
    snake_.moveOrEat({40,40});
  }
}

void Game::run() {
  while (is_running_) {
    SDL_Event event;
    handleEvents(event);
    render();
    std::cout << "The game is running.\n";
  }
}

}  // namespace gamedisplay
