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

  void setDrawColor(const SDL_Color& sdl_color) {
    if (SDL_SetRenderDrawColor(renderer_, sdl_color.r, sdl_color.g, sdl_color.b,
                               sdl_color.a) < 0) {
      throw std::runtime_error(SDL_GetError());
    }
  };

  void FillRect(SDL_FRect* rect) {
    if (SDL_RenderFillRect(renderer_, rect) < 0) {
      std::cout << "Render fills rectangle failed.\n";
    }
  }

  void clear() {
    if (SDL_RenderClear(renderer_) < 0) {
      std::runtime_error(SDL_GetError());
    }
  }

  void present() {
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

 public:
  Window(const char* title, int w, int h,
         SDL_WindowFlags flags = SDL_WINDOW_RESIZABLE) {
    window_ = SDL_CreateWindow(title, w, h, flags);
    if (window_ == nullptr) {
      throw std::runtime_error(SDL_GetError());
    }
  }

  Window(Window&& other) noexcept { std::swap(window_, other.window_); }

  Window& operator=(Window&& other) noexcept {
    if (this != &other) {
      std::swap(window_, other.window_);
    }
    return *this;
  }

  Window(const Window& other) = delete;
  Window& operator=(const Window& other) = delete;

  Renderer createRenderer() { return Renderer(window_); }

  SDL_Window* getWindow() { return window_; }

  ~Window() {
    if (window_ != nullptr) {
      SDL_DestroyWindow(window_);
    }
  }
};

inline void delay(Uint32 ms) { SDL_Delay(ms); }

}  // namespace sdl
