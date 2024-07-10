#pragma once

#include <chrono>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <deque>
#include <random>
#include <utility>

#include "dequeofunique.h"

namespace gamestatus {

enum class Direction : std::uint8_t { UP, DOWN, RIGHT, LEFT };
enum class NextState : std::uint8_t { MOVE, EAT, DIE };

class Snake {
  std::pair<int, int> getNextHead();

 protected:
  int map_width_;
  int map_height_;
  DequeOfUniquePairs<int, int> snake_body_;
  Direction head_dir_;
  std::mt19937 gen_;
  std::pair<int, int> food_;
  std::size_t size() const noexcept { return snake_body_.size(); }

  bool outOfRange(const std::pair<int, int>& element) const;
  Direction deducedDirection();

  void generateFood() {
    std::uniform_int_distribution<int> dis_width_(1, map_width_ - 1);
    std::uniform_int_distribution<int> dis_height_(1, map_height_ - 1);
    while (true) {
      int rand_x = dis_width_(gen_);
      int rand_y = dis_height_(gen_);
      food_ = std::make_pair(rand_x, rand_y);
      if (!snake_body_.has(food_)) {
        break;
      }
    }
  }

 public:
  Snake(int map_width_ = 50, int map_height_ = 50);

  const DequeOfUniquePairs<int, int>& getBody() const { return snake_body_; }

  Direction newDirection(Direction new_direction);

  NextState next();

  const std::pair<int, int>& getFood() const { return food_; }
};
}  // namespace gamestatus
