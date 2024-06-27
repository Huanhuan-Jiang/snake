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

  SDL_Window* getWindow() { return window_; }
  int getWindowWidth() { return window_width_; }
  int getWindowHeight() { return window_height_; }
  int getPixelSize() { return pixel_size_; }

 // ~Window() {   if (window_ != nullptr) {SDL_DestroyWindow(window_); } }
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
    std::cout << "renderer width: " << window_.getWindowWidth() << "\n";
    std::cout << "renderer height: " << window_.getWindowHeight() << "\n";
  };

  SDL_Renderer* getRenderer() { return renderer_; }
  

  ~Renderer() { if(renderer_!=nullptr) {SDL_DestroyRenderer(renderer_); }}

 private:
  Window window_;
  SDL_Renderer* renderer_;
};

void drawObjectAt(SDL_Renderer* renderer, std::deque<std::pair<int, int>> obj,
                  int pixel_size) {
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

class Game {
 public:
  Game(int width = 100, int height = 100, int pixel_size = 12) noexcept
      : window_width_(width),
        window_height_(height),
        pixel_size_(pixel_size),
        initialized_(true),
        game_window_(width, height, pixel_size),
        game_renderer_(game_window_)  {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
      std::cerr << "Renderer could not be created! SDL_Error:" << SDL_GetError()
                << "\n";
      initialized_ = false;
      return;
    }

   // Window game_window_(window_width_, window_height_, pixel_size_);
    window_ = game_window_.getWindow();
   // Renderer game_renderer_(game_window_);
    renderer_ = game_renderer_.getRenderer();
    gamestatus::Snake snake_(window_width_, window_height_);

    //std::cout << "Window width:" << game_window_.getWindowWidth() << ".\n";
    //std::cout << "Window height:" << game_window_.getWindowHeight() << ".\n";
    //std::cout << "Window pixel size:" << game_window_.getPixelSize() << ".\n";
  }

  bool isInitialized() { return initialized_; }

  void render() {
    SDL_SetRenderDrawColor(renderer_, 255, 255, 255, 255);
    SDL_RenderClear(renderer_);
    drawObjectAt(renderer_, snake_.getBody().deque(), pixel_size_);
    SDL_RenderPresent(renderer_);
    SDL_Delay(1000);
  }

  void run() {
    while (is_running_) {
      SDL_Event event;
      handleEvents(event);
      render();
      std::cout << "The game is running.\n";
      std::cout << "Window width:" << game_window_.getWindowWidth() << ".\n";
      //SDL_Window* windowPtr = game_window_.getWindow();
      if(window_ != nullptr) {
        std::cout << "window_ still exists.\n";
      } else {
        std::cout << "window_ doesn't exist anymore. \n";
      }
    }
  };

  void handleEvents( SDL_Event& event) {
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

  ~Game() {
    SDL_Quit();
  }

 private:
  Window game_window_;
  Renderer game_renderer_;
  SDL_Window* window_ = nullptr;
  SDL_Renderer* renderer_ = nullptr;

  bool initialized_;
  const int pixel_size_;
  const int window_width_;
  const int window_height_;

  bool is_running_ = true;

  gamestatus::Snake snake_;
};
}  // namespace gamewindow
