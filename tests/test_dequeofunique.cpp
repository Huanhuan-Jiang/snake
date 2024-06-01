#include <gmock/gmock-matchers.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <deque>
#include <stdexcept>
#include <utility>

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
