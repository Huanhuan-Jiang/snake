#pragma once

#include <SDL3/SDL.h>

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <utility>

namespace sdl {
inline void checkError(bool value) {
  if (!value) {
    throw std::runtime_error(SDL_GetError());
  }
}

class Renderer {
  SDL_Renderer* renderer_ = nullptr;

  friend class Window;

  Renderer(SDL_Window* window) {
    renderer_ = SDL_CreateRenderer(window, nullptr);
    checkError(renderer_ != nullptr);
  };

 public:
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

  void setDrawColor(const SDL_Color& sdl_color) {
    checkError(SDL_SetRenderDrawColor(renderer_, sdl_color.r, sdl_color.g,
                                      sdl_color.b, sdl_color.a) == 0);
  };

  void fillRect(SDL_FRect* rect) {
    checkError(SDL_RenderFillRect(renderer_, rect) == 0);
  }

  void clear() { checkError(SDL_RenderClear(renderer_) == 0); }

  void present() { checkError(SDL_RenderPresent(renderer_) == 0); }

  ~Renderer() {
    if (renderer_ != nullptr) {
      SDL_DestroyRenderer(renderer_);
    }
  }
};

class Window {
  SDL_Window* window_ = nullptr;

 public:
  Window() = default;

  Window(const char* title, int w, int h,
         SDL_WindowFlags flags = SDL_WINDOW_RESIZABLE) {
    window_ = SDL_CreateWindow(title, w, h, flags);
    checkError(window_ != nullptr);
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

  Renderer createRenderer() {
    if (window_ == nullptr) {
      throw std::runtime_error("Window is null!");
    }
    return Renderer(window_);
  }

  ~Window() {
    if (window_ != nullptr) {
      SDL_DestroyWindow(window_);
    }
  }
};

inline void delay(Uint32 ms) { SDL_Delay(ms); }

}  // namespace sdl
