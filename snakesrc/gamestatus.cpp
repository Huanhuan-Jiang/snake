#include "gamestatus.h"

#include <cmath>
#include <cstdint>
#include <functional>
#include <iterator>
#include <list>
#include <stdexcept>
#include <unordered_set>
#include <utility>

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

}  // namespace gamestatus
