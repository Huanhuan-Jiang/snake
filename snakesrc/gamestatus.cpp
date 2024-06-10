#include "gamestatus.h"

#include <cmath>
#include <iterator>
#include <stdexcept>
#include <unordered_set>
#include <utility>

#include "dequeofunique.h"
#include "gamestatus.h"

namespace gamestatus {

Snake::Snake(const DequeOfUniquePairs<int, int>& initial_body,
             Direction head_direction, const int map_w, const int map_h)
    : snake_body_(initial_body),
      head_dir_(head_direction),
      map_width_(map_w),
      map_height_(map_h) {
  eat_ = false;
  alive_ = true;

  // Check if the snake body is valid

  std::deque<std::pair<int, int>> snake_deque = snake_body_.deque();

  if (snake_deque.empty()) {
    throw std::runtime_error("Snake body is empty!");
  }

  auto prev_it = snake_deque.begin();
  if (prev_it->first >= map_width_ || prev_it->first <= 0 ||
      prev_it->second >= map_height_ || prev_it->second <= 0) {
    throw std::runtime_error("Snake body is beyond the map!");
  }

  for (auto it = std::next(snake_deque.begin()); it != snake_deque.end();
       ++it) {
    if (prev_it->first >= map_width_ || prev_it->first <= 0 ||
        prev_it->second >= map_height_ || prev_it->second <= 0) {
      throw std::runtime_error("Snake body is beyond the map!");
    }
    auto diff_x = std::abs(it->first - prev_it->first);
    auto diff_y = std::abs(it->second - prev_it->second);

    if (!((diff_x == 0 && diff_y == 1) || (diff_x == 1 && diff_y == 0))) {
      throw std::runtime_error("Snake body is not continuous!");
    }

    ++prev_it;
  }
}

std::pair<int, int> Snake::getNextHead() {
  auto head = snake_body_.deque().front();

  // Update the head based on the direction
  switch (head_dir_) {
    case Direction::UP:
      next_head.second++;
      break;
    case Direction::DOWN:
      next_head.second--;
      break;
    case Direction::RIGHT:
      next_head.first++;
      break;
    case Direction::LEFT:
      next_head.first--;
      break;
  }
  return head;
}

SnakeState Snake::moveOrEat(const std::pair<int, int>& food) {
  auto next_head = getNextHead();

  if (next_head.first >= map_width_ || next_head.first <= 0 ||
      next_head.second >= map_height_ || next_head.second <= 0) {
    return SnakeState::DIE;
  }  // Snake hits the wall and dies;

  if (head == food) {
    snake_body_.insertFront(head);
    return SnakeState::EAT;  // Snake eats food;
  }

  snake_body_.removeBack();
  if (snake_body_.set().find(head) != snake_body_.set().end()) {
    return SnakeState::DIE;  // Snake hits the body and dies;
  }

  snake_body_.insertFront(head);
  return SnakeState::MOVE;  // Snake moves one step alive.
}

}  // namespace gamestatus
