#pragma once

#include <deque>
#include <stdexcept>
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
      : deque_(std::move(initial_deque)),
        set_(initial_deque.begin(), initial_deque.end()) {
    if (set_.size() != initial_deque.size()) {
      throw std::runtime_error("Duplicates detected!");
    }
  };

  DequeOfUniquePairs& operator=(DequeOfUniquePairs other) {
    std::swap(deque_, other.deque_);
    std::swap(set_, other.set_);
    return *this;
  };

  bool operator==(const DequeOfUniquePairs<T1, T2>& other) const {
    return (deque_ == other.deque());
  }

  bool empty() const noexcept { return deque_.empty(); }

  const std::deque<std::pair<T1, T2>> deque() const { return deque_; };

  const std::unordered_set<std::pair<T1, T2>, pair_hash> set() const {
    return set_;
  };

  bool insertFront(std::pair<T1, T2> element) {
    if (set_.emplace(element).second) {
      deque_.emplace_front(element);
      return true;
    }
    return false;
  };

  std::size_t size() { return deque_.size(); };
  std::size_t size() const { return deque_.size(); };

  auto begin() { return deque_.begin(); }
  auto cbegin() const { return deque_.cbegin(); }

  auto end() { return deque_.end(); }
  auto cend() const { return deque_.cend(); }

  auto front() { return deque_.front(); }
  auto front() const { return deque_.front(); }

  void popBack() {
    auto last = deque_.back();
    deque_.pop_back();
    set_.erase(last);
  };

  bool has(const std::pair<T1, T2>& element) const {
    return set_.find(element) != set_.end();
  }
};

}  // namespace gamestatus
