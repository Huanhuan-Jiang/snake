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
             Direction head_direction, const Map& map)
    : snake_body_(initial_body), head_dir_(head_direction), snake_map_(map) {
  // Check if the snake body is valid

  std::deque<std::pair<int, int>> snake_deque = snake_body_.deque();

  if (snake_deque.empty()) {
    throw std::runtime_error("Snake body is empty!");
  }

  auto prev_it = snake_deque.begin();
  if (prev_it->first > snake_map_.getWidth() |
      prev_it->second > snake_map_.getHeight()) {
    throw std::runtime_error("Snake body is beyond the map!");
  }

  for (auto it = std::next(snake_deque.begin()); it != snake_deque.end();
       ++it) {
    if (prev_it->first > snake_map_.getWidth() |
        prev_it->second > snake_map_.getHeight()) {
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

bool Snake::moveOrEat(const std::pair<int, int> food) {
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

  if (head != food) {
    snake_body_.removeBack();  // Snake moves;
    if (snake_body_.set().find(head) != snake_body_.set().end()) {
      return false;  // Snake dies;
    }
  }
  snake_body_.insertFront(head);
  return true;  // Snake eats food;
}

}  // namespace gamestatus
