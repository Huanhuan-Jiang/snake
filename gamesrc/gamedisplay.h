#pragma once

#include <SDL3/SDL.h>

#include <cstddef>
#include <cstdint>
#include <deque>
#include <utility>

#include "gamestatus.h"

namespace gamedisplay {
class GameWindow {
  SDL_Window* sdl_window_ = nullptr;
  int window_width_;
  int window_height_;
  int pixel_size_;

 public:
  GameWindow(int w, int h, int pixel_size)
      : window_width_(w), window_height_(h), pixel_size_(pixel_size) {
    sdl_window_ =
        SDL_CreateWindow("Snake", window_width_ * pixel_size_,
                         window_height_ * pixel_size_, SDL_WINDOW_RESIZABLE);
  }

  SDL_Window* getWindow() { return sdl_window_; }
  int getWindowWidth() const { return window_width_; }
  int getWindowHeight() const { return window_height_; }
  int getPixelSize() const { return pixel_size_; }
};

}  // namespace gamedisplay
