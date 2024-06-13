#pragma once

#include <cmath>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
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
  std::pair<int, int> getNextHead();

 public:
  Snake(DequeOfUniquePairs<int, int> initial_body,
        const Direction head_dir_ = Direction::RIGHT, const int map_width_ = 50,
        const int map_height_ = 50);

  std::size_t size() const noexcept { return snake_body_.deque().size(); }

  const DequeOfUniquePairs<int, int>& getBody() const { return snake_body_; }

  SnakeState moveOrEat(const std::pair<int, int>& food);

  Direction updateDirection(const Direction new_direction);
};
}  // namespace gamestatus
