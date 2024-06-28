#pragma once

#include <chrono>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <ctime>
#include <deque>
#include <random>
#include <utility>

#include "dequeofunique.h"

namespace gamestatus {

enum class Direction : std::uint8_t { UP, DOWN, RIGHT, LEFT };
enum class MoveState : std::uint8_t { MOVE, EAT, DIE };

class Snake {
  DequeOfUniquePairs<int, int> snake_body_;
  Direction head_dir_;
  int map_width_;
  int map_height_;
  int64_t seed_;
  std::mt19937 gen_;
  std::uniform_int_distribution<int> dis_width_;
  std::uniform_int_distribution<int> dis_height_;
  std::pair<int, int> getNextHead();

  bool outOfRange(const std::pair<int, int>&) const;
  bool discontinuous() const noexcept;
  Direction deducedDirection();

 public:
  Snake(const DequeOfUniquePairs<int, int> initial_body,
        Direction head_dir_ = Direction::RIGHT, int map_width_ = 50,
        int map_height_ = 50,
        const int64_t seed_ =
            std::chrono::system_clock::now().time_since_epoch().count());

  Snake(int map_width_ = 50, int map_height_ = 50);

  std::size_t size() const noexcept { return snake_body_.size(); }

  const DequeOfUniquePairs<int, int>& getBody() const { return snake_body_; }

  Direction getDirection() const { return head_dir_; };

  MoveState moveOrEat(const std::pair<int, int>& food);

  Direction newDirection(Direction new_direction);

  std::pair<int, int> generateFood() {
    while (true) {
      int rand_x = dis_width_(gen_);
      int rand_y = dis_height_(gen_);
      auto food = std::make_pair(rand_x, rand_y);
      if (snake_body_.set().find(food) == snake_body_.set().end()) {
        return std::make_pair(rand_x, rand_y);
      }
    }
  }
};
}  // namespace gamestatus
