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

  bool deadSnake() {
    auto head = snake_body_.deque().front();
    auto snake_deque = snake_body_.deque();
    for (auto it = snake_deque.begin(); it != snake_deque.end(); ++it) {
      if (head == *it) {
        return false;  // Snake dies;
        break;
      }
    }
    return true;
  }

  void updateDirection(Direction new_direction) { head_dir_ = new_direction; }
};

}  // namespace gamestatus

#endif
