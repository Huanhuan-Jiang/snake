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

// Define hash for std::pair<T1, T2>
struct pair_hash {
  template <class T1, class T2>
  std::size_t operator()(const std::pair<T1, T2>& p) const {
    auto hash1 = std::hash<T1>{}(p.first);
    auto hash2 = std::hash<T2>{}(p.second);
    return hash1 ^ (hash2 << 1);
  }
};

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

  void moveOrEat(const std::pair<int, int> food);

  int deadSnake() {
    auto head = snake_body_.front();
    for (auto it = snake_body_.begin(); it != snake_body_.end(); ++it) {
      if (head == *it) {
        return 1;  // Snake dies;
        break;
      }
    }
    return 0;
  }

  void updateDirection(Direction new_direction) { head_dir_ = new_direction; }
};

class Map {
  int map_width_;
  int map_height_;

 public:
  Map(int map_w, int map_h) : map_width_(map_w), map_height_(map_h) {};

  int getWidth() { return map_width_; };
  int getHeight() { return map_height_; };

  std::pair<int, int> generateFood(
      const std::list<std::pair<int, int>>& snake_body, int width, int height);
};

}  // namespace gamestatus
