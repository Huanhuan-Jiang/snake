#include "snakestatus.h"

#include <list>
#include <utility>
#include <cstlib>
#include <stdexcept>

namespace snakestatus {

Snake::Snake(std::list<std::pair<int, int>> initial_body,
             Direction head_direction)
    : snake_body_(initial_body), head_dir_(head_direction) {
        // Check if the snake body is coninuous and alive
        for (auto it = snake_body_.begin(); it != snake_body_.end(); ++it) {
            auto head = snake_body_.front();
            auto next_it = std::next(it);
            auto diff_x = std::abs(it->first, next_it->first);
            auto diff_y = std::abs(it->second, next_it->second);
            if (snake_body_.size > 1) {
                if (head == *it | !((diff_x == 0 && diff_y == 1) | (diff_x == 1 && diff_y == 0))) {
                    throw InvalidArgumentException("Snake body is invalid!")
                }
            }
            
        }
    }

}  // namespace snakestatus
