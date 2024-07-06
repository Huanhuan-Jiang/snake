#pragma once

#include <SDL3/SDL.h>

#include <cstddef>
#include <cstdint>
#include <deque>
#include <iostream>
#include <utility>
#include <memory>

#include "gamestatus.h"

namespace gamedisplay {
class GameWindow {
  SDL_Window* sdl_window_ = nullptr;
  int window_width_ = 0;
  int window_height_ = 0;
  int pixel_size_ = 0;

 public:
  GameWindow(int w, int h, int pixel_size)
      : window_width_(w), window_height_(h), pixel_size_(pixel_size) {
    sdl_window_ =
        SDL_CreateWindow("Snake", window_width_ * pixel_size_,
                         window_height_ * pixel_size_, SDL_WINDOW_RESIZABLE);
    if(sdl_window_ ==  nullptr) {
      std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << "\n";
    }
  }

  GameWindow(GameWindow&& other) noexcept:
    window_width_(other.window_width_),
    window_height_(other.window_height_),
    pixel_size_(other.pixel_size_) {
      std::swap(sdl_window_, other.sdl_window_);
      
  }

  GameWindow& operator=(GameWindow&& other) noexcept {
    if (this != &other) {
      std::swap(sdl_window_, other.sdl_window_);
      window_width_= other.window_width_;
      window_height_= other.window_height_;
      pixel_size_= other.pixel_size_;
    }
    return *this;
  }

  GameWindow(GameWindow& other) = delete;
  GameWindow& operator=(GameWindow& other) = delete;

  SDL_Window* getWindow() { return sdl_window_; }
  int getWindowWidth() const { return window_width_; }
  int getWindowHeight() const { return window_height_; }
  int getPixelSize() const { return pixel_size_; }
};

class GameRenderer {
  std::unique_ptr<GameWindow> game_window_ = nullptr;
  SDL_Renderer* sdl_renderer_ = nullptr;

 public:
  GameRenderer() = default;

  GameRenderer(GameWindow& game_window) : game_window_(std::make_unique<GameWindow>(std::move(game_window))) {
    sdl_renderer_ = SDL_CreateRenderer(game_window_->getWindow(), nullptr);
    if (sdl_renderer_ == nullptr) {
      std::cerr << "Renderer could not be created! SDL_Error: "
                << SDL_GetError() << "\n";
    }
  };

  GameRenderer(GameRenderer&& other) noexcept {
    std::swap(sdl_renderer_, other.sdl_renderer_);
    std::swap(game_window_, other.game_window_);
  };

  GameRenderer& operator = (GameRenderer&& other) noexcept {
    if (this != &other) {
      std::swap(sdl_renderer_, other.sdl_renderer_);
      std::swap(game_window_, other.game_window_);
    }
    return *this;
  }

  GameRenderer(GameRenderer& other) = delete;
  GameRenderer& operator= (GameRenderer& other) = delete;

  SDL_Renderer* getRenderer() { return sdl_renderer_; }

  ~GameRenderer() {
    if (sdl_renderer_ != nullptr) {
      SDL_DestroyRenderer(sdl_renderer_);
    }
  }
};

void drawObjectAt(SDL_Renderer* sdl_renderer,
                  std::deque<std::pair<int, int>> obj, int pixel_size);

class Game {
 public:
  Game(int width = 50, int height = 50, int pixel_size = 12) noexcept;

  bool isInitialized() const { return initialized_; }

  void render();
  void handleEvents(SDL_Event& event);
  void run();

  ~Game() { SDL_Quit(); }

 private:
  GameRenderer game_renderer_;

  bool initialized_ = true;
  int pixel_size_;
  int window_width_;
  int window_height_;

  bool is_running_ = true;

  gamestatus::Snake snake_;
};

}  // namespace gamedisplay
