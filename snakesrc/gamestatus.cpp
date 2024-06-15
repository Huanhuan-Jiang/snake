#include "gamestatus.h"

#include <cmath>
#include <iterator>
#include <stdexcept>
#include <unordered_set>
#include <utility>

#include "dequeofunique.h"

namespace gamestatus {

DequeOfUniquePairs<int, int> initBody(const int width, const int height) {
  int mid_x = width / 2;
  int mid_y = height / 2;

  auto e1 = std::make_pair(mid_x, mid_y);
  auto e2 = std::make_pair(mid_x - 1, mid_y);
  auto e3 = std::make_pair(mid_x - 2, mid_y);
  std::deque<std::pair<int, int>> initial_deque = {e1, e2, e3};
  return DequeOfUniquePairs<int, int>(initial_deque);
}

bool Snake::outOfRange() {
  auto head_x = snake_body_.front().first;
  auto head_y = snake_body_.front().second;

  if (head_x >= map_width_ || head_x <= 0 || head_y >= map_height_ ||
      head_y <= 0) {
    return true;
  }
  return false;
}

bool Snake::continuous() {
  std::deque<std::pair<int, int>> snake_deque = snake_body_.deque();
  auto prev_it = snake_deque.begin();
  for (auto it = std::next(snake_deque.begin()); it != snake_deque.end();
       ++it) {
    auto diff_x = std::abs(it->first - prev_it->first);
    auto diff_y = std::abs(it->second - prev_it->second);

    if (!((diff_x == 0 && diff_y == 1) || (diff_x == 1 && diff_y == 0))) {
      return true;
    }
    ++prev_it;
  }
  return false;
}

Snake::Snake(DequeOfUniquePairs<int, int> initial_body,
             const Direction head_direction, const int map_w, const int map_h)
    : snake_body_(std::move(initial_body)),
      head_dir_(head_direction),
      map_width_(map_w),
      map_height_(map_h) {
  // Check if the snake body is valid

  if (snake_body_.empty()) {
    throw std::runtime_error("Snake body is empty!");
  }

  if (outOfRange()) {
    throw std::runtime_error("Snake body is beyond the map!");
  }

  if (continuous()) {
    throw std::runtime_error("Snake body is not continuous!");
  }
}

std::pair<int, int> Snake::getNextHead() {
  auto head = snake_body_.deque().front();

  // Update the head based on the direction
  switch (head_dir_) {
    case Direction::UP:
      head.second++;
      break;
    case Direction::DOWN:
      head.second--;
      break;
    case Direction::RIGHT:
      head.first++;
      break;
    case Direction::LEFT:
      head.first--;
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

  if (next_head == food) {
    snake_body_.insertFront(next_head);
    return SnakeState::EAT;  // Snake eats food;
  }

  snake_body_.removeBack();
  if (snake_body_.set().find(next_head) != snake_body_.set().end()) {
    return SnakeState::DIE;  // Snake hits the body and dies;
  }

  snake_body_.insertFront(next_head);
  return SnakeState::MOVE;  // Snake moves one step alive.
}

Direction Snake::updateDirection(const Direction new_direction) {
  switch (head_dir_) {
    case Direction::UP:
    case Direction::DOWN:
      if (new_direction != Direction::DOWN && new_direction != Direction::UP) {
        head_dir_ = new_direction;
      }
      break;
    case Direction::LEFT:
    case Direction::RIGHT:
      if (new_direction != Direction::RIGHT &&
          new_direction != Direction::LEFT) {
        head_dir_ = new_direction;
      }
      break;
    default:
      break;
  }
  return (head_dir_);
}

}  // namespace gamestatus
