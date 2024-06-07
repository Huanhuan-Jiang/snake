#ifndef GAMESTATUS_H
#define GAMESTATUS_H

#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <ctime>
// #include <list>
#include <random>
#include <utility>

#include "dequeofunique.h"

namespace gamestatus {

enum class Direction : std::uint8_t { UP, DOWN, RIGHT, LEFT };

class Snake {
  gamestatus::DequeOfUniquePairs<int, int> snake_body_;
  Direction head_dir_;

 public:
  Snake(const DequeOfUniquePairs<int, int>& initial_body,
        Direction head_direction);

  std::size_t size() const noexcept { return snake_body_.deque().size(); }

  const DequeOfUniquePairs<int, int>& getBody() const { return snake_body_; }

  const Direction& getDirection() const { return head_dir_; };

  void moveOrEat(const std::pair<int, int> food);

  int deadSnake() {
    auto head = snake_body_.deque().front();
    auto snake_deque = snake_body_.deque();
    for (auto it = snake_deque.begin(); it != snake_deque.end();
         ++it) {
      if (head == *it) {
        return 1;  // Snake dies;
        break;
      }
    }
    return 0;
  }

  void updateDirection(Direction new_direction) { head_dir_ = new_direction; }
};

class Map {
  int map_width_;
  int map_height_;

 public:
  Map(int map_w, int map_h) : map_width_(map_w), map_height_(map_h) {}

  int getWidth() { return map_width_; };
  int getHeight() { return map_height_; };

  std::pair<int, int> generateFood(
      const DequeOfUniquePairs<int, int>& snake_body);
};

}  // namespace gamestatus

#endif
