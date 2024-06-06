#pragma once

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

  const std::deque<std::pair<T1, T2>> deque() const { return deque_; };

  const std::unordered_set<std::pair<T1, T2>, pair_hash> set() const {
    return set_;
  };

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
}  // namespace gamestatus
