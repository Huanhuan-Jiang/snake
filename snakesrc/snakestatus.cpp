#include "snakestatus.h"

#include <list>
#include <utility>

namespace snakestatus {

Snake::Snake(std::list<std::pair<int, int>> initial_body,
             Direction head_direction)
    : snake_body_(initial_body), head_dir_(head_direction) {}

}  // namespace snakestatus
