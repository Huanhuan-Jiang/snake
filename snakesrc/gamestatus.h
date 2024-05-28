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

  std::pair<int, int> generateFood() {
    auto seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 gen(seed);
    std::uniform_int_distribution<int> dis(1, 100);

    int rand_x = dis(gen);
    int rand_y = dis(gen);
    return std::make_pair(rand_x, rand_y);
  };
};

}  // namespace gamestatus
