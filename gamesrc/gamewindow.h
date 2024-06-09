#pragma once

#include <SDL3/SDL.h>

#include <cstddef>
#include <cstdint>
#include <deque>
#include <iostream>
#include <utility>

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
  SDL_Window* window_;
  SDL_Renderer* renderer_;
}

void render(SDL_Renderer* renderer, std::deque<std::pair<int, int>> object, int delay=100) {
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  SDL_RenderClear(renderer);
  drawObjectAt(renderer, object);
  SDL_RenderPresent(renderer);
  SDL_Delay(delay);
}

void drawObjectAt(SDL_Renderer* renderer_,
                  std::deque<std::pair<int, int>> obj) {
  for (auto& element : obj) {
    logicalX = element.first;
    logicalY = element.second;

    SDL_FRect rect = {static_cast<float>(logicalX * pixel_size_),
                      static_cast<float>(logicalY * pixel_size_),
                      static_cast<float>(pixel_size_),
                      static_cast<float>(pixel_size_)};
    SDL_SetRenderDrawColor(renderer_, 255, 0, 0, 255);  // Red
    SDL_RenderFillRect(renderer_, &rect);
  }
}

class Game {
 public:
  Game(int width = default_window_width, int height = default_window_height,
       int pixel_size = default_pixel_size) noexcept
      : window_width_(width), window_height_(height), pixel_size_(pixel_size) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
      std::cerr << "Renderer could not be created! SDL_Error:" << SDL_GetError()
                << "\n";
      initialized_ = false;
      return;
    }

    Window game_window;
    window_ = game_window.getWindow();
    Renderer game_renderer;
    rederer = renderer
  }

  void run() {
    while (is_running_) {
      handleEvents();
      // update();
      render();
    }
  };

 private:
  SDL_Window* window_ = nullptr;
  SDL_Renderer* renderer_ = nullptr;

  static constexpr int default_pixel_size = 12;
  static constexpr int default_window_width = 100;
  static constexpr int default_window_height = 100;

  bool initialized_;

  const int pixel_size_;
  const int window_width_;
  const int window_height_;

  bool is_running_ = true;

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
}
}  // namespace gamewindow
