#include "snakestatus.h"
#include <utility>
#include <vector>

namespace snakestatus {

Snake::Snake(std::vector<std::pair<int, int>> initialBody,
             Direction headDirection)
    : snakeBody(initialBody), headDir(headDirection) {}

}  // namespace snakestatus
