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

void drawFoodAt(SDL_Renderer* sdl_renderer, std::pair<int, int> obj,
                int pixel_size) {
  auto logicalX = obj.first;
  auto logicalY = obj.second;

  SDL_FRect rect = {static_cast<float>(logicalX * pixel_size),
                    static_cast<float>(logicalY * pixel_size),
                    static_cast<float>(pixel_size),
                    static_cast<float>(pixel_size)};
  SDL_SetRenderDrawColor(sdl_renderer, 185, 87, 86, 255);
  SDL_RenderFillRect(sdl_renderer, &rect);
}

Game::Game(int width, int height, int pixel_size) noexcept
    : window_width_(width),
      window_height_(height),
      pixel_size_(pixel_size),
      snake_(width, height) {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL_Error:" << SDL_GetError() << "\n";
    initialized_ = false;
    return;
  }

  GameWindow game_window(width, height, pixel_size);
  GameRenderer game_renderer(game_window);
  game_renderer_ = std::move(game_renderer);
}

void Game::render() {
  SDL_SetRenderDrawColor(game_renderer_.getRenderer(), 255, 255, 255, 255);
  SDL_RenderClear(game_renderer_.getRenderer());
  drawObjectAt(game_renderer_.getRenderer(), snake_.getBody().deque(), pixel_size_);
  SDL_RenderPresent(game_renderer_.getRenderer());
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
            snake_.newDirection(gamestatus::Direction::UP);
            break;
          case SDL_SCANCODE_DOWN:
            snake_.newDirection(gamestatus::Direction::DOWN);
            break;
          case SDL_SCANCODE_LEFT:
            snake_.newDirection(gamestatus::Direction::LEFT);
            break;
          case SDL_SCANCODE_RIGHT:
            snake_.newDirection(gamestatus::Direction::RIGHT);
            break;
        }
      default:
        break;
    }
  }

  snake_.next();
  // switch (snake_.next()){
  //   case: gamestatus::NextState::EAT:
  //     drawObjectAt
  // }
}

void Game::run() {
  while (is_running_) {
    SDL_Event event;
    handleEvents(event);
    render();
  }
}

}  // namespace gamedisplay
