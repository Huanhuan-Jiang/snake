#pragma once

#include <SDL3/SDL.h>

#include <cstddef>
#include <cstdint>
#include <deque>
#include <iostream>
#include <utility>

#include "dequeofunique.h"
#include "gamestatus.h"

namespace gamedisplay {
class GameWindow {
  SDL_Window* sdl_window_ = nullptr;
  int window_width_;
  int window_height_;
  int pixel_size_;

 public:
  GameWindow(int w, int h, int pixel_size);
  SDL_Window* getWindow() { return sdl_window_; }
  int getWindowWidth() const { return window_width_; }
  int getWindowHeight() const { return window_height_; }
  int getPixelSize() const { return pixel_size_; }
}

class GameRenderer {
  GameWindow game_window_;
  SDL_Renderer* sdl_renderer_ = nullptr;

 public:
  GameRenderer(GameWindow game_window) : game_window_(game_window) {
    sdl_renderer_ = SDL_CreateRenderer(game_window_.getWindow(), nullptr);
    if (sdl_renderer_ == nullptr) {
      std::cerr << "Renderer could not be created! SDL_Error: "
                << SDL_GetError() << "\n";
      return;
    }
  };

  SDL_Renderer* getRenderer() { return sdl_renderer_; }

  ~GameRenderer() {
    if (sdl_renderer_ != nullptr) {
      SDL_DestroyRenderer(sdl_renderer_);
    }
  }
};

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

class Game {
 public:
  Game(int width = 50, int height = 50, int pixel_size = 12) noexcept
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

  bool isInitialized() const { return initialized_; }

  void render() {
    SDL_SetRenderDrawColor(sdl_renderer_, 255, 255, 255, 255);
    SDL_RenderClear(sdl_renderer_);
    drawObjectAt(sdl_renderer_, snake_.getBody().deque(), pixel_size_);
    SDL_RenderPresent(sdl_renderer_);
    SDL_Delay(1000);
  }

  void run() {
    while (is_running_) {
      SDL_Event event;
      handleEvents(event);
      render();
      std::cout << "The game is running.\n";
    }
  };

  void handleEvents(SDL_Event& event) {
    while (SDL_PollEvent(&event)) {
      switch (event.type) {
        case SDL_EVENT_QUIT:
          is_running_ = false;
          break;
        default:
          break;
      }
    }
  }

  ~Game() { SDL_Quit(); }

 private:
  GameWindow game_window_;
  GameRenderer game_renderer_;
  SDL_Window* sdl_window_ = nullptr;
  SDL_Renderer* sdl_renderer_ = nullptr;

  bool initialized_ = true;
  int pixel_size_;
  int window_width_;
  int window_height_;

  bool is_running_ = true;

  gamestatus::Snake snake_;
};
}  // namespace gamewindow
