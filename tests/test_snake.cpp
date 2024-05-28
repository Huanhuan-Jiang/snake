#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <list>
#include <stdexcept>
#include <utility>

#include "gamestatus.h"

using testing::HasSubstr;
using testing::Property;
using testing::Throws;

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

  std::list<std::pair<std::list<std::pair<int, int>>, std::string>>
      illegal_cases = {{illegalbody1, "Snake body is not continuous!"},
                       {illegalbody2, "Snake body is not continuous!"},
                       {illegalbody3, "Snake body overlaps!"},
                       {illegalbody4, "Snake body overlaps!"},
                       {illegalbody5, "Snake body overlaps!"}};

  for (const auto& [illegalbody, error_message] : illegal_cases) {
    EXPECT_THAT(
        [&illegalbody]() {
          gamestatus::Snake illegalsnake(illegalbody,
                                         gamestatus::Direction::RIGHT);
        },
        Throws<std::runtime_error>(Property(&std::runtime_error::what,
                                            HasSubstr(error_message.c_str()))));
  }
}

TEST_F(SnakeTest, SnakeSize) {
  gamestatus::Snake snake1_0(body1_0, gamestatus::Direction::RIGHT);
  gamestatus::Snake snake9_4(body9_4, gamestatus::Direction::RIGHT);

  EXPECT_EQ(snake1_0.size(), 1u);
  EXPECT_EQ(snake9_4.size(), 9u);
}

TEST_F(SnakeTest, GetBody) {
  gamestatus::Snake snake1_0(body1_0, gamestatus::Direction::RIGHT);
  gamestatus::Snake snake9_4(body9_4, gamestatus::Direction::RIGHT);

  EXPECT_EQ(snake1_0.getBody(), body1_0);
  EXPECT_EQ(snake9_4.getBody(), body9_4);
}

TEST_F(SnakeTest, GetDirection) {
  gamestatus::Snake snake1_0_right(body1_0, gamestatus::Direction::RIGHT);
  gamestatus::Snake snake9_4_right(body9_4, gamestatus::Direction::RIGHT);
  gamestatus::Snake snake1_0_left(body1_0, gamestatus::Direction::LEFT);
  gamestatus::Snake snake9_4_left(body9_4, gamestatus::Direction::LEFT);
  gamestatus::Snake snake1_0_up(body1_0, gamestatus::Direction::UP);
  gamestatus::Snake snake9_4_up(body9_4, gamestatus::Direction::UP);
  gamestatus::Snake snake1_0_down(body1_0, gamestatus::Direction::DOWN);
  gamestatus::Snake snake9_4_down(body9_4, gamestatus::Direction::DOWN);

  EXPECT_EQ(snake1_0_right.getDirection(), gamestatus::Direction::RIGHT);
  EXPECT_EQ(snake9_4_right.getDirection(), gamestatus::Direction::RIGHT);
  EXPECT_EQ(snake1_0_left.getDirection(), gamestatus::Direction::LEFT);
  EXPECT_EQ(snake9_4_left.getDirection(), gamestatus::Direction::LEFT);
  EXPECT_EQ(snake1_0_up.getDirection(), gamestatus::Direction::UP);
  EXPECT_EQ(snake9_4_up.getDirection(), gamestatus::Direction::UP);
  EXPECT_EQ(snake1_0_down.getDirection(), gamestatus::Direction::DOWN);
  EXPECT_EQ(snake9_4_down.getDirection(), gamestatus::Direction::DOWN);
}

TEST(ToolsTest, GenerateFood) {
  std::pair<int, int> food = gamestatus::generateFood(500, 500); // Assuming map_width = 500, map_height = 500
  EXPECT_THAT(food.first, testing::AllOf(testing::Ge(1), testing::Le(500)));
  EXPECT_THAT(food.second, testing::AllOf(testing::Ge(1), testing::Le(500)));
}