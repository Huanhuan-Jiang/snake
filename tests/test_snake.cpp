#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <list>
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

TEST_F(SnakeTest, SnakeThrowExceptionOnIllegalSnake) {
  std::list<std::pair<int, int>> illegal1 = {
      {20, 30}, {19, 30}, {19, 29}, {18, 28}, {17, 29},
      {17, 28}, {17, 27}, {16, 27}, {15, 27}};  // not continuous
  std::list<std::pair<int, int>> illegal2 = {
      {20, 30}, {19, 30}, {19, 29}, {17, 28}, {17, 29},
      {17, 28}, {17, 27}, {16, 27}, {15, 27}};  // not continuous
  std::list<std::pair<int, int>> illegal3 = {
      {20, 30}, {19, 30}, {19, 29}, {19, 29}, {17, 29},
      {17, 28}, {17, 27}, {16, 27}, {15, 27}};  // duplicate elements
  std::list<std::pair<int, int>> illegal4 = {
      {19, 29}, {19, 30}, {19, 29}, {18, 29}, {17, 29},
      {17, 28}, {17, 27}, {16, 27}, {15, 27}};  // duplicate elements
  std::list<std::pair<int, int>> illegal5 = {
      {17, 29}, {17, 30}, {18, 30}, {19, 30}, {19, 29}, {18, 29},
      {17, 29}, {17, 28}, {17, 27}, {16, 27}, {15, 27}};  // duplicate elements

  EXPECT_THROW(
      {snakestatus::Snake snake1(illegal1, snakestatus::Direction::RIGHT);},
      std::runtime_error);
  EXPECT_THROW(
      {snakestatus::Snake snake1(illegal2, snakestatus::Direction::RIGHT);},
      std::runtime_error);
  EXPECT_THROW(
      {snakestatus::Snake snake1(illegal3, snakestatus::Direction::RIGHT);},
      std::runtime_error);
  EXPECT_THROW(
      {snakestatus::Snake snake1(illegal4, snakestatus::Direction::RIGHT);},
      std::runtime_error);
  EXPECT_THROW(
      {snakestatus::Snake snake1(illegal5, snakestatus::Direction::RIGHT);},
      std::runtime_error);
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
  std::list<std::pair<int, int>> expected1 = {{21, 30}, {20, 30}};
  char a;  // Unused variable

  snakestatus::Snake snake1_0(body1_0, snakestatus::Direction::RIGHT);
  snakestatus::Snake snake9_4(body9_4, snakestatus::Direction::RIGHT);

  EXPECT_EQ(snake1_0.getDirection(), snakestatus::Direction::RIGHT);
  EXPECT_EQ(snake9_4.getDirection(), snakestatus::Direction::RIGHT);
}
