#pragma once

#include <cstddef>
#include <cstdint>
#include <deque>
#include <list>
#include <unordered_set>
#include <utility>

namespace gamestatus {

// Define hash for std::pair<T1, T2>
struct pair_hash {
  template <class T1, class T2>
  std::size_t operator()(const std::pair<T1, T2>& p) const {
    auto hash1 = std::hash<T1>{}(p.first);
    auto hash2 = std::hash<T2>{}(p.second);
    return hash1 ^ (hash2 << 1);
  }
};

template <typename T1, typename T2>
class DequeOfUniquePairs {
  std::deque<std::pair<T1, T2>> deque_;
  std::unordered_set<std::pair<T1, T2>, pair_hash> set_;

 public:
  DequeOfUniquePairs(const std::deque<std::pair<T1, T2>> initial_deque)
      : deque_(std::move(initial_deque)) {
    for (auto it = deque_.begin(); it != deque_.end(); ++it) {
      set_.insert(*it);
    }
  };

  const std::deque<std::pair<T1, T2>> deque() const { return deque_; };

  const std::unordered_set<std::pair<T1, T2>> set() const { return set_; };

  void insertFront(std::pair<T1, T2> element) {
    deque_.emplace_front(element);
    set_.insert(element);
  };

  void removeBack() {
    auto last = deque_.back();
    deque_.pop_back();
    set_.erase(last);
  };
};

enum class Direction : std::uint8_t { UP, DOWN, RIGHT, LEFT };

class Snake {
  // The (x, y) coordinates of each piece of the snake body
  std::list<std::pair<int, int>> snake_body_;

  // The direction of snake head
  Direction head_dir_;

 public:
  Snake(std::list<std::pair<int, int>> initial_body, Direction head_direction);

  std::size_t size() const noexcept { return snake_body_.size(); }

  const std::list<std::pair<int, int>>& getBody() const { return snake_body_; }

  const Direction& getDirection() const { return head_dir_; };
};

}  // namespace gamestatus
