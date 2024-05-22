#pragma once

#include <utility>
#include <vector>

namespace snakestatus {

enum class Direction { UP, DOWN, RIGHT, LEFT };

class Snake {
  // The (x, y) coordinates of each piece of the snake body
  std::vector<std::pair<int, int>> snake_body_;

  // The direction of snake head
  Direction head_dir_;

 public:
  Snake(std::vector<std::pair<int, int>> initial_body,
        Direction head_direction);

  std::size_t size() const noexcept { return snake_body_.size(); }

  const std::vector<std::pair<int, int>>& getBody() const {
    return snake_body_;
  }

  // The length of the snake's body increases by one unit after consuming the
  // food.
  void eatFood(std::pair<int, int>& food) {
    snake_body_.insert(snake_body_.begin(), food);
  };

  const Direction& getDirection() const { return head_dir_; };
};

}  // namespace snakestatus
