#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <list>
#include <stdexcept>
#include <utility>

#include "snakestatus.h"

class SnakeTest : public ::testing::Test {
 protected:
  void SetUp() override {
    body1_0 = {{20, 30}};  // one unit long
    body9_4 = {{20, 30}, {19, 30}, {19, 29}, {18, 29}, {17, 29},
               {17, 28}, {17, 27}, {16, 27}, {15, 27}};  // nine units long with
                                                         // 4 turns
  }

  std::list<std::pair<int, int>> body1_0;
  std::list<std::pair<int, int>> body9_4;
};

TEST_F(SnakeTest, SnakeThrowExceptionWithCorrectMessage) {
  std::list<std::pair<int, int>> illegalbody1 = {
      {20, 30}, {19, 30}, {19, 29}, {18, 28}, {17, 29},
      {17, 28}, {17, 27}, {16, 27}, {15, 27}};  // not continuous
  std::list<std::pair<int, int>> illegalbody2 = {
      {20, 30}, {19, 30}, {19, 29}, {17, 28}, {17, 29},
      {17, 28}, {17, 27}, {16, 27}, {15, 27}};  // not continuous
  std::list<std::pair<int, int>> illegalbody3 = {
      {20, 30}, {19, 30}, {19, 29}, {19, 29}, {17, 29},
      {17, 28}, {17, 27}, {16, 27}, {15, 27}};  // duplicate elements
  std::list<std::pair<int, int>> illegalbody4 = {
      {19, 29}, {19, 30}, {19, 29}, {18, 29}, {17, 29},
      {17, 28}, {17, 27}, {16, 27}, {15, 27}};  // duplicate elements
  std::list<std::pair<int, int>> illegalbody5 = {
      {17, 29}, {17, 30}, {18, 30}, {19, 30}, {19, 29}, {18, 29},
      {17, 29}, {17, 28}, {17, 27}, {16, 27}, {15, 27}};  // duplicate elements

  std::list<std::pair<std::list<std::pair<int, int>>, std::string>> illegal_cases = {
    {illegalbody1, "Snake body is not continuous!"},
    {illegalbody2, "Snake body is not continuous!"},
    {illegalbody3, "Snake body overlaps!"},
    {illegalbody4, "Snake body overlaps!"},
    {illegalbody5, "Snake body overlaps!"}
  };

  for(const auto& [illegalbody, error_message] : illegal_cases) {
    try {
      EXPECT_THROW(
        {
          snakestatus::Snake illegalsnake(illegalbody,
                                           snakestatus::Direction::RIGHT);
        },
        std::runtime_error);
    } catch (const std::runtime_error& e) {
      EXPECT_STREQ(e.what(), error_message);
    }
  }
}

TEST_F(SnakeTest, SnakeSize) {
  snakestatus::Snake snake1_0(body1_0, snakestatus::Direction::RIGHT);
  snakestatus::Snake snake9_4(body9_4, snakestatus::Direction::RIGHT);

  EXPECT_EQ(snake1_0.size(), 1u);
  EXPECT_EQ(snake9_4.size(), 9u);
}

TEST_F(SnakeTest, GetBody) {
  snakestatus::Snake snake1_0(body1_0, snakestatus::Direction::RIGHT);
  snakestatus::Snake snake9_4(body9_4, snakestatus::Direction::RIGHT);

  EXPECT_EQ(snake1_0.getBody(), body1_0);
  EXPECT_EQ(snake9_4.getBody(), body9_4);
}

TEST_F(SnakeTest, GetDirection) {
  snakestatus::Snake snake1_0_right(body1_0, snakestatus::Direction::RIGHT);
  snakestatus::Snake snake9_4_right(body9_4, snakestatus::Direction::RIGHT);
  snakestatus::Snake snake1_0_left(body1_0, snakestatus::Direction::LEFT);
  snakestatus::Snake snake9_4_left(body9_4, snakestatus::Direction::LEFT);
  snakestatus::Snake snake1_0_up(body1_0, snakestatus::Direction::UP);
  snakestatus::Snake snake9_4_up(body9_4, snakestatus::Direction::UP);
  snakestatus::Snake snake1_0_down(body1_0, snakestatus::Direction::DOWN);
  snakestatus::Snake snake9_4_down(body9_4, snakestatus::Direction::DOWN);

  EXPECT_EQ(snake1_0_right.getDirection(), snakestatus::Direction::RIGHT);
  EXPECT_EQ(snake9_4_right.getDirection(), snakestatus::Direction::RIGHT);
  EXPECT_EQ(snake1_0_left.getDirection(), snakestatus::Direction::LEFT);
  EXPECT_EQ(snake9_4_left.getDirection(), snakestatus::Direction::LEFT);
  EXPECT_EQ(snake1_0_up.getDirection(), snakestatus::Direction::UP);
  EXPECT_EQ(snake9_4_up.getDirection(), snakestatus::Direction::UP);
  EXPECT_EQ(snake1_0_down.getDirection(), snakestatus::Direction::DOWN);
  EXPECT_EQ(snake9_4_down.getDirection(), snakestatus::Direction::DOWN);
}
