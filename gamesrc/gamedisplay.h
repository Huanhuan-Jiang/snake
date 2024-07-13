#pragma once

#include <SDL3/SDL.h>

#include <cstddef>
#include <cstdint>
#include <deque>
#include <iostream>
#include <utility>

#include "gamestatus.h"
#include "sdl.h"

namespace gamedisplay {
class Game {
 public:
  Game(const char* title, int width = 50, int height = 50,
       int pixel_size = 12) noexcept;

  bool isInitialized() const { return initialized_; }

  void render();
  void handleEvents(SDL_Event& event);
  void run();
  void drawElement(const std::pair<int, int>& obj, const SDL_Color& sdl_color);
  void drawBody(const std::deque<std::pair<int, int>>& obj,
                const SDL_Color& sdl_color);

  ~Game() { SDL_Quit(); }

 private:
  sdl::Window window_;
  sdl::Renderer renderer_;
  int pixel_size_;
  bool initialized_ = true;
  bool is_running_ = true;
  int score_ = 0;

  gamestatus::Snake snake_;
};

}  // namespace gamedisplay
