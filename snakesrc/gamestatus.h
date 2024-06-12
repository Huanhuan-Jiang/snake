#pragma once

#include <chrono>
#include <cmath>  // std::floor
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <random>
#include <utility>

#include "dequeofunique.h"

namespace gamestatus {

enum class Direction : std::uint8_t { UP, DOWN, RIGHT, LEFT };
enum class SnakeState : std::uint8_t { MOVE, EAT, DIE };

inline DequeOfUniquePairs<int, int> initBody(int width = 50, int height = 50) {
  auto e1 = std::make_pair(std::floor(width / 2), std::floor(height / 2));
  auto e2 = std::make_pair(std::floor(width / 2) - 1, std::floor(height / 2));
  auto e3 = std::make_pair(std::floor(width / 2) - 2, std::floor(height / 2));
  std::deque<std::pair<int, int>> initial_deque = {e1, e2, e3};
  return DequeOfUniquePairs<int, int>(initial_deque);
}

class Snake {
  DequeOfUniquePairs<int, int> snake_body_;
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
        Direction head_dir_ = Direction::RIGHT, const int map_width_ = 50,
        const int map_height_ = 50,
        int64_t seed_ =
            std::chrono::system_clock::now().time_since_epoch().count());

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

  void printBody() {
    std::cout << "The snake body is: ";
    for (auto& element : snake_body_.deque()) {
      std::cout << "{" << element.first << ", " << element.second << "} ";
    }
    std::cout << ".\n";
  }
};
}  // namespace gamestatus
