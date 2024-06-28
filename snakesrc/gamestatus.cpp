#include "gamestatus.h"

#include <cmath>
#include <iterator>
#include <stdexcept>
#include <utility>
#include <iostream> //delete later

#include "dequeofunique.h"

namespace gamestatus {

namespace {
DequeOfUniquePairs<int, int> initBody(int width, int height) {
  int mid_x = width / 2;
  int mid_y = height / 2;

  auto e1 = std::make_pair(mid_x, mid_y);
  auto e2 = std::make_pair(mid_x - 1, mid_y);
  auto e3 = std::make_pair(mid_x - 2, mid_y);
  std::deque<std::pair<int, int>> initial_deque = {e1, e2, e3};
  return DequeOfUniquePairs<int, int>(std::move(initial_deque));
}

bool isOpposite(Direction dir1, Direction dir2) {
  return ((dir1 == Direction::UP && dir2 == Direction::DOWN) ||
          (dir1 == Direction::DOWN && dir2 == Direction::UP) ||
          (dir1 == Direction::RIGHT && dir2 == Direction::LEFT) ||
          (dir1 == Direction::LEFT && dir2 == Direction::RIGHT));
}
}  // namespace

bool Snake::outOfRange(const std::pair<int, int>& element) const {
  auto [x, y] = element;
  return (x >= map_width_ || x < 0 || y >= map_height_ || y < 0);
}

bool Snake::discontinuous() const noexcept {
  auto prev_it = snake_body_.cbegin();
  for (auto it = std::next(snake_body_.cbegin()); it != snake_body_.cend();
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

Direction Snake::deducedDirection() {
  if (snake_body_.size() >= 2u) {
    auto head_it = snake_body_.begin();
    auto next_it = std::next(head_it);

    auto diff_x = head_it->first - next_it->first;
    auto diff_y = head_it->second - next_it->second;

    if (diff_x == 0 && diff_y == 1) {
      return Direction::DOWN;
    }

    if (diff_x == 0 && diff_y == -1) {
      return Direction::UP;
    }

    if (diff_x == 1 && diff_y == 0) {
      return Direction::RIGHT;
    }

    if (diff_x == -1 && diff_y == 0) {
      return Direction::LEFT;
    }

    throw std::invalid_argument("Invalid direction values");
  }
  return head_dir_;
}

Snake::Snake(DequeOfUniquePairs<int, int> initial_body,
             Direction head_direction, int map_w, int map_h, int64_t seed)
    : snake_body_(std::move(initial_body)),
      head_dir_(head_direction),
      map_width_(map_w),
      map_height_(map_h),
      seed_(seed),
      gen_(seed_),
      dis_width_(1, map_width_ - 1),
      dis_height_(1, map_height_ - 1) {
  // Check if the snake body is valid
  if (snake_body_.empty()) {
    throw std::runtime_error("Snake body is empty!");
  }

  for (auto element : snake_body_) {
    if (outOfRange(element)) {
      throw std::runtime_error("Snake body is beyond the map!");
    }
  }

  if (discontinuous()) {
    throw std::runtime_error("Snake body is not continuous!");
  }

  if (isOpposite(deducedDirection(), head_dir_)) {
    throw std::runtime_error("The head direction is invalid!");
  }

  generateFood();
  //std::cout << "The first food is now at (" << food_.first <<", " << food_.second << ").\n"; //delete later
}

Snake::Snake(int map_width_, int map_height_)
    : Snake(initBody(map_width_, map_height_), Direction::RIGHT, map_width_,
            map_height_) {};  // Todo: do i need to initialize seed?

std::pair<int, int> Snake::getNextHead() {
  std::pair<int, int> head = snake_body_.front();

  switch (head_dir_) {
    case Direction::UP:
      head.second--;
      break;
    case Direction::DOWN:
      head.second++;
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

MoveState Snake::moveOrEat() {
  auto next_head = getNextHead();

  if (outOfRange(next_head)) {
    return MoveState::DIE;
  }  // Snake hits the wall and dies;

  if (next_head == food_) {
    snake_body_.insertFront(next_head);
    generateFood();
    //std::cout << "new food is now at (" << food_.first <<", " << food_.second << ").\n"; //delete later
    return MoveState::EAT;  // Snake eats food;
  }

  snake_body_.popBack();
  if (!snake_body_.insertFront(next_head)) {
    return MoveState::DIE;  // Snake hits the body and dies;
  }

  return MoveState::MOVE;  // Snake moves one step alive
}

Direction Snake::newDirection(Direction new_direction) {
  if (!isOpposite(deducedDirection(), new_direction)) {
    head_dir_ = new_direction;
  }
  return head_dir_;
}

}  // namespace gamestatus
