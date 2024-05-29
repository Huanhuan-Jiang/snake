#include "gamestatus.h"

#include <cmath>
#include <iterator>
#include <list>
#include <stdexcept>
#include <unordered_set>
#include <utility>

#include "dequeofunique.h"

namespace gamestatus {

Snake::Snake(std::list<std::pair<int, int>> initial_body,
             Direction head_direction)
    : snake_body_(std::move(initial_body)), head_dir_(head_direction) {
  // Check if the snake body is coninuous and alive
  auto prev_it = snake_body_.begin();
  std::unordered_set<std::pair<int, int>, pair_hash> unique_elements;
  unique_elements.insert(*prev_it);
  for (auto it = std::next(snake_body_.begin()); it != snake_body_.end();
       ++it) {
    auto diff_x = std::abs(it->first - prev_it->first);
    auto diff_y = std::abs(it->second - prev_it->second);
    if (unique_elements.find(*it) != unique_elements.end()) {
      throw std::runtime_error("Snake body overlaps!");
    }
    if (!((diff_x == 0 && diff_y == 1) || (diff_x == 1 && diff_y == 0))) {
      throw std::runtime_error("Snake body is not continuous!");
    }
    unique_elements.insert(*it);
    ++prev_it;
  }
}

void Snake::move() {
  auto head = snake_body_.front();

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
  // Move all elements one step further
  std::rotate(snake_body_.rbegin(), std::next(snake_body_.rbegin()),
              snake_body_.rend());

  snake_body_.pop_front();
  snake_body_.push_front(head);
}

std::pair<int, int> Map::generateFood(
    const std::list<std::pair<int, int>>& snake_body, int width, int height) {
  std::unordered_set<std::pair<int, int>, pair_hash> snake_body_set(
      snake_body.begin(), snake_body.end());
  auto seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::mt19937 gen(seed);
  std::uniform_int_distribution<int> dis_width(1, width);
  std::uniform_int_distribution<int> dis_height(1, height);

  while (true) {
    int rand_x = dis_width(gen);
    int rand_y = dis_height(gen);
    auto food = std::make_pair(rand_x, rand_y);
    if (snake_body_set.find(food) == snake_body_set.end()) {
      return std::make_pair(rand_x, rand_y);
    }
  }
};

}  // namespace gamestatus
