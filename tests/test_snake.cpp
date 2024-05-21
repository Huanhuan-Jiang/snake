#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <vector>

#include "snakestatus.h"

// define test fixutre
class SnakeTest : public ::testing::Test {
 protected:
  // initialize the snake bodies
  void SetUp() override {
    body1_0 = {{20, 30}};  // one unit long
    body9_4 = {{20, 30}, {19, 30}, {19, 29}, {18, 29}, {17, 29},
               {17, 28}, {17, 27}, {16, 27}, {15, 27}};  // nine units long with
                                                         // 4 turns
  }

  std::vector<std::pair<int, int>> body1_0;
  std::vector<std::pair<int, int>> body9_4;
};

TEST_F(SnakeTest, SnakeSize) {
  snakestatus::Snake snake1_0(body1_0, snakestatus::Direction::RIGHT);
  snakestatus::Snake snake9_4(body9_4, snakestatus::Direction::RIGHT);

  EXPECT_EQ(snake1_0.size(), 1) << "The SnakeSize with snake1_0 failed";
  EXPECT_EQ(snake9_4.size(), 9) << "The SnakeSize with snake9_4 failed";
}

TEST_F(SnakeTest, GetBody) {
  snakestatus::Snake snake1_0(body1_0, snakestatus::Direction::RIGHT);
  snakestatus::Snake snake9_4(body9_4, snakestatus::Direction::RIGHT);

  EXPECT_EQ(snake1_0.getBody(), body1_0) << "The getBody with snake1_0 failed";
  EXPECT_EQ(snake9_4.getBody(), body9_4) << "The getBody with snake9_4 failed";
}

TEST_F(SnakeTest, EatFood) {
  std::pair<int, int> food = {21, 30};
  std::vector<std::pair<int, int>> expected1_0 = {{21, 30}, {20, 30}};
  std::vector<std::pair<int, int>> expected9_4 = {
      {21, 30}, {20, 30}, {19, 30}, {19, 29}, {18, 29},
      {17, 29}, {17, 28}, {17, 27}, {16, 27}, {15, 27}};

  snakestatus::Snake snake1_0(body1_0, snakestatus::Direction::RIGHT);
  snakestatus::Snake snake9_4(body9_4, snakestatus::Direction::RIGHT);

  snake1_0.eatFood(food);
  snake9_4.eatFood(food);

  EXPECT_EQ(snake1_0.getBody(), expected1_0) << "EatFood with snake1_0 failed";
  EXPECT_EQ(snake9_4.getBody(), expected9_4) << "EatFood with snake9_4 failed";
}

TEST_F(SnakeTest, GetDirection) {
  std::vector<std::pair<int, int>> expected1_0 = {{20, 30}};
  std::vector<std::pair<int, int>> expected9_4 = {{20, 30}, {19, 30}, {19, 29}, {18, 29}, {17, 29},
               {17, 28}, {17, 27}, {16, 27}, {15, 27}};

  snakestatus::Snake snake1_0(body1_0, snakestatus::Direction::RIGHT);
  snakestatus::Snake snake9_4(body9_4, snakestatus::Direction::RIGHT);

  EXPECT_EQ(snake1_0.getDirection(), snakestatus::Direction::RIGHT) << "GetDirection with snake1_0 failed";
  EXPECT_EQ(snake9_4.getDirection(), snakestatus::Direction::RIGHT) << "GetDirection with snake9_4 failed";
}
