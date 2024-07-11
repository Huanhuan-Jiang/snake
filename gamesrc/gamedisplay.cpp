#include <SDL3/SDL.h>

#include <cstddef>
#include <cstdint>
#include <deque>
#include <iostream>
#include <stdexcept>
#include <utility>

#include "gamestatus.h"
#include "gamedisplay.h"
#include "sdl.h"

namespace gamedisplay {

Game::Game(int width, int height, int pixel_size) noexcept
    : window_width_(width),
      window_height_(height),
      pixel_size_(pixel_size),
      snake_(width, height),
      window_(width, height, pixel_size) {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    initialized_ = false;
  }

  renderer_ = window_.createRenderer();
}

void Game::drawElement(const std::pair<int, int>& obj, int pixel_size,
                       const SDL_Color& color) {
  auto logicalX = obj.first;
  auto logicalY = obj.second;

  SDL_FRect rect = {static_cast<float>(logicalX * pixel_size),
                     static_cast<float>(logicalY * pixel_size),
                     static_cast<float>(pixel_size),
                     static_cast<float>(pixel_size)};

  renderer_.setRenderDrawColor(color);
  renderer_.renderFillRect(&rect);
}

void Game::drawBody(const std::deque<std::pair<int, int>>& obj, int pixel_size,
                    const SDL_Color& color) {
  for (auto& element : obj) {
    drawElement(element, pixel_size, color);
  }
}

void Game::render() {
  SDL_Color bkg_color = {255, 255, 255, 255};
  SDL_Color food_color = {185, 87, 86, 255};
  SDL_Color body_color = {42, 76, 101, 255};
  Uint32 time_ms = 300;

  renderer_.setRenderDrawColor(bkg_color);
  renderer_.renderClear();
  drawElement(snake_.getFood(), pixel_size_, food_color);
  drawBody(snake_.getBody().deque(), pixel_size_, body_color);
  renderer_.renderPresent();
  sdl::delay(time_ms);
}

void Game::handleEvents(SDL_Event& event) {
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
      case SDL_EVENT_QUIT:
        is_running_ = false;
        break;
      case SDL_EVENT_KEY_DOWN:
        switch ((event.key.scancode)) {
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
          default:
            break;
        }
      default:
        break;
    }
  }

  snake_.next();
}

void Game::run() {
  while (is_running_) {
    SDL_Event event;
    handleEvents(event);
    render();
  }
}

}  // namespace gamedisplay
