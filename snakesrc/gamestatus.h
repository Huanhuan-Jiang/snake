#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <ctime>
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

  bool moveOrEat(const std::pair<int, int> food);

  void updateDirection(Direction new_direction) { head_dir_ = new_direction; }
};

}  // namespace gamestatus
