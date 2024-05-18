// This is the declaration of namespace snakestatus
#pragma once
#include <cmath>
#include <utility>
#include <vector>

namespace snakestatus {
enum class Direction { UP, DOWN, RIGHT, LEFT };
// definition of class Snake
class Snake {
 private:
  std::vector<std::pair<int, int>> snakeBody;
  int head_X;
  int head_Y;
  Direction headDir;

 public:
  // Constructor
  Snake();
  Snake(std::vector<std::pair<int, int>> initialBody, Direction headDirection);

  // Get the size of snake body
  int size();
  // Get the body of snake
  std::vector<std::pair<int, int>> getBody();
  // Move the snake one step further based on its head's direction
  void move();
  void eatFood(std::pair<int, int>);
  Direction getDirection();
};
}  // namespace snakestatus