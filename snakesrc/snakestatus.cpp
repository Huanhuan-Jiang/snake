#include <utility>
#include <vector>

#include "snakestatus.h"

namespace snakestatus {

Snake::Snake(std::vector<std::pair<int, int>> initial_body,
             Direction head_direction)
    : snake_body_(initial_body), head_dir_(head_direction) {}

}
