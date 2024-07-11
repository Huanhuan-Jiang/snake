#pragma once

#include <SDL3/SDL.h>

#include <cstddef>
#include <cstdint>
#include <deque>
#include <iostream>
#include <memory>
#include <utility>

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
    if (sdl_window_ == nullptr) {
      throw std::runtime_error(SDL_GetError());
    }
  }

  GameWindow(GameWindow&& other) noexcept
      : window_width_(other.window_width_),
        window_height_(other.window_height_),
        pixel_size_(other.pixel_size_) {
    std::swap(sdl_window_, other.sdl_window_);
  }

  GameWindow& operator=(GameWindow&& other) noexcept {
    if (this != &other) {
      std::swap(sdl_window_, other.sdl_window_);
      window_width_ = other.window_width_;
      window_height_ = other.window_height_;
      pixel_size_ = other.pixel_size_;
    }
    return *this;
  }

  GameWindow(const GameWindow& other) = delete;
  GameWindow& operator=(const GameWindow& other) = delete;

  SDL_Window* getWindow() { return sdl_window_; }
  int getWindowWidth() const { return window_width_; }
  int getWindowHeight() const { return window_height_; }
  int getPixelSize() const { return pixel_size_; }
};

class GameRenderer {
  std::unique_ptr<GameWindow> game_window_ = nullptr;
  SDL_Renderer* sdl_renderer_ = nullptr;
  SDL_Color* sdl_color_ = nullptr;

 public:
  GameRenderer() = default;

  GameRenderer(std::unique_ptr<GameWindow> game_window)
      : game_window_(std::move(game_window)) {
    sdl_renderer_ = SDL_CreateRenderer(game_window_->getWindow(), nullptr);
    if (sdl_renderer_ == nullptr) {
      throw std::runtime_error(SDL_GetError());
    }
  };

  GameRenderer(GameRenderer&& other) noexcept {
    std::swap(sdl_renderer_, other.sdl_renderer_);
    std::swap(game_window_, other.game_window_);
  };

  GameRenderer& operator=(GameRenderer&& other) noexcept {
    if (this != &other) {
      std::swap(sdl_renderer_, other.sdl_renderer_);
      std::swap(game_window_, other.game_window_);
    }
    return *this;
  }

  GameRenderer(const GameRenderer& other) = delete;
  GameRenderer& operator=(const GameRenderer& other) = delete;

  SDL_Renderer* getRenderer() { return sdl_renderer_; }

  void setRenderDrawColor(const SDL_Color& sdl_color) {
    if (SDL_SetRenderDrawColor(sdl_renderer_, sdl_color.r, sdl_color.g,
                               sdl_color.b, sdl_color.a) < 0) {
      throw std::runtime_error(SDL_GetError());
    }
  };

  void renderClear() {
    if (SDL_RenderClear(sdl_renderer_) < 0) {
      std::runtime_error(SDL_GetError());
    }
  }

  void renderPresent() {
    if (SDL_RenderPresent(sdl_renderer_) < 0) {
      std::runtime_error(SDL_GetError());
    }
  }

  void drawElement(const std::pair<int, int>& obj, int pixel_size,
                   const SDL_Color& sdl_color);

  void drawBody(const std::deque<std::pair<int, int>>& obj, int pixel_size,
                const SDL_Color& sdl_color);

  ~GameRenderer() {
    if (sdl_renderer_ != nullptr) {
      SDL_DestroyRenderer(sdl_renderer_);
    }
  }
};

void delay(Uint32 ms);

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
  bool is_running_ = true;
  int pixel_size_;
  int window_width_;
  int window_height_;
  int score_ = 0;

  gamestatus::Snake snake_;
};

}  // namespace gamedisplay
