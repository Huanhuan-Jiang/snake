#pragma once

#include <cmath>
#include <cstdint>
#include <deque>
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
  std::pair<int, int> getNextHead();

  bool outOfRange(const std::pair<int, int>&) const;
  bool discontinuous() const noexcept;
  Direction deducedDirection();

 public:
  Snake(const DequeOfUniquePairs<int, int> initial_body,
        Direction head_dir_ = Direction::RIGHT, int map_width_ = 50,
        int map_height_ = 50);

  Snake(int map_width_ = 50, int map_height_ = 50);

  std::size_t size() const noexcept { return snake_body_.size(); }

  const DequeOfUniquePairs<int, int>& getBody() const { return snake_body_; }

  Direction getDirection() const { return head_dir_; };

  MoveState moveOrEat(const std::pair<int, int>& food);

  Direction newDirection(Direction new_direction);
};
}  // namespace gamestatus
