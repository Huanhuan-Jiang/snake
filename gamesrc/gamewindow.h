#pragma once

#include <SDL3/SDL.h>

#include <cstddef>
#include <cstdint>
#include <deque>
#include <iostream>
#include <utility>

#include "dequeofunique.h"
#include "gamestatus.h"

namespace gamewindow {
class Window {
  SDL_Window* window_;
  int window_width_;
  int window_height_;
  int pixel_size_;

 public:
  Window(int w, int h, int pixel_size)
      : window_width_(w), window_height_(h), pixel_size_(pixel_size) {
    window_ =
        SDL_CreateWindow("Snake", window_width_ * pixel_size_,
                         window_height_ * pixel_size_, SDL_WINDOW_RESIZABLE);
  }

  SDL_Window* getWindow() { return window_; };

  ~Window() { SDL_DestroyWindow(window_); }
};

class Renderer {
 public:
  Renderer(Window window) : window_(window) {
    renderer_ = SDL_CreateRenderer(window_.getWindow(), nullptr);
    if (renderer_ == nullptr) {
      std::cerr << "Renderer could not be created! SDL_Error: "
                << SDL_GetError() << "\n";
      return;
    }
  };

  SDL_Renderer* getRenderer(){return renderer_;}

  ~Renderer() { SDL_DestroyRenderer(renderer_); }

 private:
  Window window_;
  SDL_Renderer* renderer_;
};

void drawObjectAt(SDL_Renderer* renderer,
                  std::deque<std::pair<int, int>> obj, int pixel_size) {
  for (auto& element : obj) {
    auto logicalX = element.first;
    auto logicalY = element.second;

    SDL_FRect rect = {static_cast<float>(logicalX * pixel_size),
                      static_cast<float>(logicalY * pixel_size),
                      static_cast<float>(pixel_size),
                      static_cast<float>(pixel_size)};
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);  // Red
    SDL_RenderFillRect(renderer, &rect);
  }
}

void render(SDL_Renderer* renderer, std::deque<std::pair<int, int>> object, int pixel_size=12, int delay=100) {
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  SDL_RenderClear(renderer);
  drawObjectAt(renderer, object, pixel_size);
  SDL_RenderPresent(renderer);
  SDL_Delay(delay);
}

class Game {
 public:
  Game(gamestatus::Snake snake, int width = 50, int height = 50,
       int pixel_size = 12) noexcept
      : snake_(snake), window_width_(width), window_height_(height), pixel_size_(pixel_size) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
      std::cerr << "Renderer could not be created! SDL_Error:" << SDL_GetError()
                << "\n";
      initialized_ = false;
      return;
    }

    Window game_window(window_width_, window_height_, pixel_size_);
    window_ = game_window.getWindow();
    Renderer game_renderer(game_window);
    renderer_ = game_renderer.getRenderer();
    snake_(window_width_, window_height_);
    
  }
  
  void run() {
    while (is_running_) {
      handleEvents();
      render(renderer_, );
    }
  };

 private:
  SDL_Window* window_ = nullptr;
  SDL_Renderer* renderer_ = nullptr;

  // Todo Check if initialized is necessary.
  bool initialized_;
  const int pixel_size_;
  const int window_width_;
  const int window_height_;

  bool is_running_ = true;

  gamestatus::Snake snake_;

  void handleEvents() {
    SDL_Event event;
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
};
}  // namespace gamewindow
