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
  bool eat_;
  bool alive_;
  std::pair<int, int> getNextHead();

 public:
  Snake(const DequeOfUniquePairs<int, int>& initial_body,
        Direction head_direction, const int map_w, const int map_h);

  std::size_t size() const noexcept { return snake_body_.deque().size(); }

  const DequeOfUniquePairs<int, int>& getBody() const { return snake_body_; }

  const Direction& getDirection() const { return head_dir_; };

  SnakeState moveOrEat(const std::pair<int, int>& food);

  void updateDirection(Direction new_direction) { head_dir_ = new_direction; }
};

}  // namespace gamestatus
