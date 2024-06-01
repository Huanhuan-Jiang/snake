#include <gmock/gmock-matchers.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <algorithm>
#include <deque>
#include <stdexcept>
#include <unordered_set>
#include <utility>
#include <vector>

#include "gamestatus.h"

using testing::HasSubstr;
using testing::Property;
using testing::Throws;

TEST(DequeOfUniqueTest, ThrowExceptionWithCorrectMessage) {
  std::deque<std::pair<int, int>> deque1 = {
      {20, 30}, {19, 30}, {19, 29},
      {18, 28}, {19, 29}, {18, 28}};  // duplicate elements
  std::deque<std::pair<int, int>> deque2 = {
      {19, 29}, {19, 30}, {19, 29}, {18, 29}};  // duplicate elements

  const std::deque<std::pair<std::deque<std::pair<int, int>>, std::string>>
      illegal_cases = {{deque1, "Duplicates detected!"},
                       {deque2, "Duplicates detected!"}};

  for (const auto& [illegaldeque, error_message] : illegal_cases) {
    auto lambda = [&illegaldeque]() {
      gamestatus::DequeOfUniquePairs<int, int> deque_unique(illegaldeque);
    };

    EXPECT_THAT(lambda,
                Throws<std::runtime_error>(Property(&std::runtime_error::what,
                                                    HasSubstr(error_message))));
  }
}

TEST(DequeOfUniqueTest, ReturnDequeAndSet) {
  std::deque<std::pair<int, int>> deque1 = {
      {20, 30}, {19, 30}, {19, 29}, {18, 28}};
  std::deque<std::pair<int, int>> deque2 = {
      {19, 29}, {19, 30}, {19, 31}, {18, 29}};

  std::unordered_set<std::pair<int, int>, gamestatus::pair_hash> set1 = {
      {20, 30}, {19, 30}, {19, 29}, {18, 28}};
  std::unordered_set<std::pair<int, int>, gamestatus::pair_hash> set2 = {
      {19, 29}, {19, 30}, {19, 31}, {18, 29}};

  gamestatus::DequeOfUniquePairs<int, int> deque_unique1(deque1);
  gamestatus::DequeOfUniquePairs<int, int> deque_unique2(deque2);
  EXPECT_EQ(deque_unique1.deque(), deque1);
  EXPECT_EQ(deque_unique2.deque(), deque2);
  EXPECT_EQ(deque_unique1.set(), set1);
  EXPECT_EQ(deque_unique2.set(), set2);
}

TEST(DequeOfUniqueTest, InsertFrontAndCheckDequeAndSet) {
  std::pair<int, int> head = {15, 15};

  std::deque<std::pair<int, int>> deque1 = {
      {20, 30}, {19, 30}, {19, 29}, {18, 28}};
  std::deque<std::pair<int, int>> deque2 = {
      {19, 29}, {19, 30}, {19, 31}, {18, 29}};

  std::deque<std::pair<int, int>> expect_deque1 = {
      {15, 15}, {20, 30}, {19, 30}, {19, 29}, {18, 28}};
  std::deque<std::pair<int, int>> expect_deque2 = {
      {15, 15}, {19, 29}, {19, 30}, {19, 31}, {18, 29}};

  std::unordered_set<std::pair<int, int>, gamestatus::pair_hash> expect_set1 = {
      {15, 15}, {20, 30}, {19, 30}, {19, 29}, {18, 28}};
  std::unordered_set<std::pair<int, int>, gamestatus::pair_hash> expect_set2 = {
      {15, 15}, {19, 29}, {19, 30}, {19, 31}, {18, 29}};

  gamestatus::DequeOfUniquePairs<int, int> deque_unique1(deque1);
  deque_unique1.insertFront(head);
  EXPECT_EQ(deque_unique1.deque(), expect_deque1);
  EXPECT_EQ(deque_unique1.set(), expect_set1);

  gamestatus::DequeOfUniquePairs<int, int> deque_unique2(deque2);
  deque_unique2.insertFront(head);
  EXPECT_EQ(deque_unique2.deque(), expect_deque2);
  EXPECT_EQ(deque_unique2.set(), expect_set2);
}

TEST(DequeOfUniqueTest, RemoveBackAndCheckDequeAndSet) {
  std::deque<std::pair<int, int>> deque1 = {
      {20, 30}, {19, 30}, {19, 29}, {18, 28}};
  std::deque<std::pair<int, int>> deque2 = {
      {19, 29}, {19, 30}, {19, 31}, {18, 29}};

  std::deque<std::pair<int, int>> expect_deque1 = {
      {20, 30}, {19, 30}, {19, 29}};
  std::deque<std::pair<int, int>> expect_deque2 = {
      {19, 29}, {19, 30}, {19, 31}};

  std::unordered_set<std::pair<int, int>, gamestatus::pair_hash> expect_set1 = {
      {20, 30}, {19, 30}, {19, 29}};
  std::unordered_set<std::pair<int, int>, gamestatus::pair_hash> expect_set2 = {
      {19, 29}, {19, 30}, {19, 31}};

  gamestatus::DequeOfUniquePairs<int, int> deque_unique1(deque1);
  deque_unique1.removeBack();
  EXPECT_EQ(deque_unique1.deque(), expect_deque1);
  EXPECT_EQ(deque_unique1.set(), expect_set1);

  gamestatus::DequeOfUniquePairs<int, int> deque_unique2(deque2);
  deque_unique2.removeBack();
  EXPECT_EQ(deque_unique2.deque(), expect_deque2);
  EXPECT_EQ(deque_unique2.set(), expect_set2);
}
