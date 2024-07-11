#include "gamedisplay.h"

#include <SDL3/SDL.h>

#include <cstddef>
#include <cstdint>
#include <deque>
#include <iostream>
#include <stdexcept>
#include <utility>

#include "gamestatus.h"

namespace gamedisplay {

void delay(Uint32 ms) { SDL_Delay(ms); }

void GameRenderer::drawElement(const std::pair<int, int>& obj, int pixel_size,
                               const SDL_Color& sdl_color) {
  auto logicalX = obj.first;
  auto logicalY = obj.second;

  SDL_FRect rect = {static_cast<float>(logicalX * pixel_size),
                    static_cast<float>(logicalY * pixel_size),
                    static_cast<float>(pixel_size),
                    static_cast<float>(pixel_size)};
  SDL_SetRenderDrawColor(sdl_renderer_, sdl_color.r, sdl_color.g, sdl_color.b,
                         sdl_color.a);
  SDL_RenderFillRect(sdl_renderer_, &rect);
}

void GameRenderer::drawBody(const std::deque<std::pair<int, int>>& obj,
                            int pixel_size, const SDL_Color& sdl_color) {
  for (auto& element : obj) {
    GameRenderer::drawElement(element, pixel_size, sdl_color);
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
    initialized_ = false;
  }

  std::unique_ptr<GameWindow> game_window =
      std::make_unique<GameWindow>(width, height, pixel_size);
  GameRenderer game_renderer(std::move(game_window));
  game_renderer_ = std::move(game_renderer);
}

void Game::render() {
  SDL_Color bkg_color = {255, 255, 255, 255};
  SDL_Color food_color = {185, 87, 86, 255};
  SDL_Color body_color = {42, 76, 101, 255};
  Uint32 time_ms = 300;

  game_renderer_.setRenderDrawColor(bkg_color);
  game_renderer_.renderClear();
  game_renderer_.drawElement(snake_.getFood(), pixel_size_, food_color);
  game_renderer_.drawBody(snake_.getBody().deque(), pixel_size_, body_color);
  game_renderer_.renderPresent();
  delay(time_ms);
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
