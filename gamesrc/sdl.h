#pragma once

#include <SDL3/SDL.h>

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <utility>

namespace sdl {
class Renderer {
  SDL_Renderer* renderer_ = nullptr;

 public:
  Renderer() = default;

  Renderer(SDL_Window* window) {
    renderer_ = SDL_CreateRenderer(window, nullptr);
    if (renderer_ == nullptr) {
      throw std::runtime_error(SDL_GetError());
    }
  };

  Renderer(Renderer&& other) noexcept {
    std::swap(renderer_, other.renderer_);
  };

  Renderer& operator=(Renderer&& other) noexcept {
    if (this != &other) {
      std::swap(renderer_, other.renderer_);
    }
    return *this;
  }

  Renderer(const Renderer& other) = delete;
  Renderer& operator=(const Renderer& other) = delete;

  SDL_Renderer* getRenderer() { return renderer_; }

  void setRenderDrawColor(const SDL_Color& sdl_color) {
    if (SDL_SetRenderDrawColor(renderer_, sdl_color.r, sdl_color.g, sdl_color.b,
                               sdl_color.a) < 0) {
      throw std::runtime_error(SDL_GetError());
    }
  };

  void renderFillRect(SDL_FRect* rect) {
    if (SDL_RenderFillRect(renderer_, rect) < 0) {
      std::cout << "Render fills rectangle failed.\n";
    }
  }

  void renderClear() {
    if (SDL_RenderClear(renderer_) < 0) {
      std::runtime_error(SDL_GetError());
    }
  }

  void renderPresent() {
    if (SDL_RenderPresent(renderer_) < 0) {
      std::runtime_error(SDL_GetError());
    }
  }

  ~Renderer() {
    if (renderer_ != nullptr) {
      SDL_DestroyRenderer(renderer_);
    }
  }
};

class Window {
  SDL_Window* window_ = nullptr;
  int window_width_ = 0;
  int window_height_ = 0;
  int pixel_size_ = 0;

 public:
  Window(int w, int h, int pixel_size)
      : window_width_(w), window_height_(h), pixel_size_(pixel_size) {
    window_ =
        SDL_CreateWindow("Snake", window_width_ * pixel_size_,
                         window_height_ * pixel_size_, SDL_WINDOW_RESIZABLE);
    if (window_ == nullptr) {
      throw std::runtime_error(SDL_GetError());
    }
  }

  Window(Window&& other) noexcept
      : window_width_(other.window_width_),
        window_height_(other.window_height_),
        pixel_size_(other.pixel_size_) {
    std::swap(window_, other.window_);
  }

  Window& operator=(Window&& other) noexcept {
    if (this != &other) {
      std::swap(window_, other.window_);
      window_width_ = other.window_width_;
      window_height_ = other.window_height_;
      pixel_size_ = other.pixel_size_;
    }
    return *this;
  }

  Window(const Window& other) = delete;
  Window& operator=(const Window& other) = delete;

  Renderer createRenderer() { return Renderer(window_); }

  SDL_Window* getWindow() { return window_; }
  int getWindowWidth() const { return window_width_; }
  int getWindowHeight() const { return window_height_; }
  int getPixelSize() const { return pixel_size_; }
};

inline void delay(Uint32 ms) { SDL_Delay(ms); }

}  // namespace sdl
