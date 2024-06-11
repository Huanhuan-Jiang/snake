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
enum class SnakeState : std::uint8_t { MOVE, EAT, DIE };

class Snake {
  gamestatus::DequeOfUniquePairs<int, int> snake_body_;
  Direction head_dir_;
  int map_width_;
  int map_height_;
  int seed_;
  std::mt19937 gen_;
  std::uniform_int_distribution<int> dis_width_;
  std::uniform_int_distribution<int> dis_height_;
  std::pair<int, int> getNextHead();

 public:
  Snake(const DequeOfUniquePairs<int, int>& initial_body,
        Direction head_direction, const int map_w, const int map_h);

  Snake(const DequeOfUniquePairs<int, int>& initial_body,
        Direction head_direction, const int map_w, const int map_h, int seed);

  std::size_t size() const noexcept { return snake_body_.deque().size(); }

  const DequeOfUniquePairs<int, int>& getBody() const { return snake_body_; }

  const Direction& getDirection() const { return head_dir_; }

  SnakeState moveOrEat(const std::pair<int, int>& food);

  void updateDirection(const Direction new_direction);

  std::pair<int, int> generateFood() {
    while (true) {
      int rand_x = dis_width_(gen_);
      int rand_y = dis_height_(gen_);
      auto food = std::make_pair(rand_x, rand_y);
      if (snake_body_.set().find(food) == snake_body_.set().end()) {
        return std::make_pair(rand_x, rand_y);
      }
    }
  };
};
}  // namespace gamestatus
