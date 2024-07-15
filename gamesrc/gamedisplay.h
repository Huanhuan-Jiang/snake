#pragma once

#include <SDL3/SDL.h>

#include <cstddef>
#include <cstdint>
#include <deque>
#include <iostream>
#include <memory>
#include <utility>

#include "gamestatus.h"
#include "sdl.h"

namespace gamedisplay {
class Game {
 public:
  Game(const char* title, int width = 50, int height = 50, int pixel_size = 12);
  void run();
  ~Game() { SDL_Quit(); }

 private:
  void handleEvents();
  void render();

  void drawElement(const std::pair<int, int>& obj, const SDL_Color& sdl_color);
  void drawBody(const std::deque<std::pair<int, int>>& obj,
                const SDL_Color& sdl_color);

  std::unique_ptr<sdl::Window> window_ = nullptr;
  std::unique_ptr<sdl::Renderer> renderer_ = nullptr;

  int pixel_size_;
  bool is_running_ = true;

  gamestatus::Snake snake_;
};

}  // namespace gamedisplay
