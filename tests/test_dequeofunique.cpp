#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <deque>
#include <stdexcept>
#include <utility>

#include "gamestatus.h"

TEST(DequeOfUniqueTest, Deque) {
  std::deque<std::pair<int, int>> deque1 = {
      {20, 30}, {19, 30}, {19, 29}, {18, 28}};
  std::deque<std::pair<int, int>> deque2 = {
      {19, 29}, {19, 30}, {19, 29}, {18, 29}};  // duplicate elements
  std::deque<std::pair<int, int>> deque3 = {
      {19, 29}, {19, 29}, {18, 30}, {19, 30}, {19, 29}};  // duplicate elements

  gamestatus::DequeOfUniquePairs<int, int> deque_unique1(deque1);
  gamestatus::DequeOfUniquePairs<int, int> deque_unique2(deque2);
  gamestatus::DequeOfUniquePairs<int, int> deque_unique3(deque3);
  
  EXPECT_EQ(deque_unique1.deque(), deque1);
  EXPECT_EQ(deque_unique2.deque(), deque2);
  EXPECT_EQ(deque_unique3.deque(), deque3);
}
