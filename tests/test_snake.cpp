#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <deque>
#include <iostream>
#include <list>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

#include "dequeofunique.h"
#include "gamestatus.h"

using testing::HasSubstr;
using testing::Property;
using testing::Throws;

TEST(SnakeTest, SnakeThrowExceptionWithCorrectMessage) {
  std::deque<std::pair<int, int>> illegaldeque0 = {};  // empty body
  std::deque<std::pair<int, int>> illegaldeque1 = {
      {20, 30}, {19, 30}, {19, 29}, {18, 28}, {17, 29},
      {17, 28}, {17, 27}, {16, 27}, {15, 27}};  // not continuous
  std::deque<std::pair<int, int>> illegaldeque2 = {
      {20, 30}, {19, 30}, {19, 29}, {17, 28}, {17, 29}};  // not continuous

  std::vector<std::pair<gamestatus::DequeOfUniquePairs<int, int>, std::string>>
      illegal_cases = {{gamestatus::DequeOfUniquePairs<int, int>(illegaldeque0),
                        "Snake body is empty!"},
                       {gamestatus::DequeOfUniquePairs<int, int>(illegaldeque1),
                        "Snake body is not continuous!"},
                       {gamestatus::DequeOfUniquePairs<int, int>(illegaldeque2),
                        "Snake body is not continuous!"}};

  for (const auto& [illegalbody, error_message] : illegal_cases) {
    EXPECT_THAT(
        [&illegalbody]() {
          gamestatus::Snake illegalsnake(illegalbody,
                                         gamestatus::Direction::RIGHT);
        },
        Throws<std::runtime_error>(
            Property(&std::runtime_error::what, HasSubstr(error_message))));
  }
}

TEST(SnakeTest, SnakeSize) {
  gamestatus::DequeOfUniquePairs<int, int> body1({{20, 30}});  // one unit long
  gamestatus::DequeOfUniquePairs<int, int>  body9({{20, 30}, {19, 30}, {19, 29}, {18, 29}, {17, 29},
               {17, 28}, {17, 27}, {16, 27}, {15, 27}});
  gamestatus::Snake snake1(body1, gamestatus::Direction::RIGHT);
  gamestatus::Snake snake9(body9, gamestatus::Direction::RIGHT);

  EXPECT_EQ(snake1.size(), 1u);
  EXPECT_EQ(snake9.size(), 9u);
}

TEST(SnakeTest, GetBody) {
  gamestatus::DequeOfUniquePairs<int, int> body1({{20, 30}});  // one unit long
  gamestatus::DequeOfUniquePairs<int, int>  body9({{20, 30}, {19, 30}, {19, 29}, {18, 29}, {17, 29},
               {17, 28}, {17, 27}, {16, 27}, {15, 27}});
  gamestatus::Snake snake1(body1, gamestatus::Direction::RIGHT);
  gamestatus::Snake snake9(body9, gamestatus::Direction::RIGHT);

  EXPECT_EQ(snake1.getBody().deque(), body1.deque());
  EXPECT_EQ(snake9.getBody().deque(), body9.deque());
  EXPECT_EQ(snake1.getBody().set(), body1.set());
  EXPECT_EQ(snake9.getBody().set(), body9.set());
}

TEST(SnakeTest, GetDirection) {
  gamestatus::DequeOfUniquePairs<int, int>  body9({{20, 30}, {19, 30}, {19, 29}, {18, 29}, {17, 29},
               {17, 28}, {17, 27}, {16, 27}, {15, 27}});

  gamestatus::Snake snake9_right(body9, gamestatus::Direction::RIGHT);
  gamestatus::Snake snake9_left(body9, gamestatus::Direction::LEFT);
  gamestatus::Snake snake9_up(body9, gamestatus::Direction::UP);
  gamestatus::Snake snake9_down(body9, gamestatus::Direction::DOWN);

  EXPECT_EQ(snake9_right.getDirection(), gamestatus::Direction::RIGHT);
  EXPECT_EQ(snake9_left.getDirection(), gamestatus::Direction::LEFT);
  EXPECT_EQ(snake9_up.getDirection(), gamestatus::Direction::UP);
  EXPECT_EQ(snake9_down.getDirection(), gamestatus::Direction::DOWN);
}