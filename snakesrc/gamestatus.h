#pragma once

#include <chrono>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <random>
#include <utility>

#include "dequeofunique.h"

namespace gamestatus {

enum class Direction : std::uint8_t { UP, DOWN, RIGHT, LEFT };
enum class SnakeState : std::uint8_t { MOVE, EAT, DIE };

DequeOfUniquePairs<int, int> initBody(int width = 50, int height = 50);

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

 public:
  Snake(DequeOfUniquePairs<int, int> initial_body,
        const Direction head_dir_ = Direction::RIGHT, const int map_width_ = 50,
        const int map_height_ = 50,
        const int64_t seed_ =
            std::chrono::system_clock::now().time_since_epoch().count());

  std::size_t size() const noexcept { return snake_body_.deque().size(); }

  const DequeOfUniquePairs<int, int>& getBody() const { return snake_body_; }

  SnakeState moveOrEat(const std::pair<int, int>& food);

  Direction updateDirection(const Direction new_direction);

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
