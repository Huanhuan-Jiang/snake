#include "gamestatus.h"

#include <cmath>
#include <iterator>
#include <stdexcept>
#include <utility>

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

Snake::Snake(DequeOfUniquePairs<int, int> initial_body,
             Direction head_direction, int map_w, int map_h)
    : snake_body_(std::move(initial_body)),
      head_dir_(head_direction),
      map_width_(map_w),
      map_height_(map_h) {
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
}

Snake::Snake(int map_width_, int map_height_)
    : Snake(initBody(map_width_, map_height_), Direction::RIGHT, map_width_,
            map_height_) {};

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

MoveState Snake::moveOrEat(const std::pair<int, int>& food) {
  auto next_head = getNextHead();

  if (outOfRange(next_head)) {
    return MoveState::DIE;
  }  // Snake hits the wall and dies;

  if (next_head == food) {
    snake_body_.insertFront(next_head);
    return MoveState::EAT;  // Snake eats food;
  }

  snake_body_.popBack();
  if (!snake_body_.insertFront(next_head)) {
    return MoveState::DIE;  // Snake hits the body and dies;
  }

  return MoveState::MOVE;  // Snake moves one step alive
}

Direction Snake::updateDirection(Direction new_direction) {
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
  return head_dir_;
}

}  // namespace gamestatus
