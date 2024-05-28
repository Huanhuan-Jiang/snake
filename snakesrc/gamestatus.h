#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <ctime>
#include <list>
#include <random>
#include <utility>

namespace gamestatus {

enum class Direction : std::uint8_t { UP, DOWN, RIGHT, LEFT };

class Snake {
  // The (x, y) coordinates of each piece of the snake body
  std::list<std::pair<int, int>> snake_body_;

  // The direction of snake head
  Direction head_dir_;

 public:
  Snake(std::list<std::pair<int, int>> initial_body, Direction head_direction);

  std::size_t size() const noexcept { return snake_body_.size(); }

  const std::list<std::pair<int, int>>& getBody() const { return snake_body_; }

  const Direction& getDirection() const { return head_dir_; };

  void move();

  void eatFood(std::pair<int, int> food) {
    snake_body_.insert(snake_body_.begin(), food);
  };
};

inline std::pair<int, int> generateFood(int map_width, int map_height) {
  auto seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::mt19937 gen(seed);
  std::uniform_int_distribution<int> dis_width(1, map_width);
  std::uniform_int_distribution<int> dis_height(1, map_height);

  int rand_x = dis_width(gen);
  int rand_y = dis_height(gen);
  return std::make_pair(rand_x, rand_y);
};

}  // namespace gamestatus
