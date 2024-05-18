// This is the definition of the namespace snakestatus
#include "snakestatus.h"

#include <iostream>
#include <utility>
#include <vector>

namespace snakestatus {

Snake::Snake(std::vector<std::pair<int, int>> initialBody,
             Direction headDirection)
    : snakeBody(initialBody), headDir(headDirection) {}

// Get the size of snake body
int Snake::size() { return snakeBody.size(); }
}  // namespace snakestatus
