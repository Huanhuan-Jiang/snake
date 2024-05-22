#pragma once

#include <utility>
#include <vector>

namespace snakestatus {

enum class Direction { UP, DOWN, RIGHT, LEFT };

// definition of class Snake
class Snake {

  std::vector<std::pair<int, int>> snake_body_;
  Direction head_dir_;

 public:
  Snake(std::vector<std::pair<int, int>> initialBody, Direction head_direction);

  int size() { return snake_body_.size(); }

  std::vector<std::pair<int, int>> getBody() { return snake_body_; };

  void eatFood(std::pair<int, int> food) {
    snake_body_.insert(snake_body_.begin(), food);
  };

  Direction getDirection() { return head_dir_; };

  void move();
  
};

}  // namespace snakestatus
