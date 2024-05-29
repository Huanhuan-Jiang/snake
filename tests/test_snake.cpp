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
    body12_3 = {{18, 29}, {18, 28}, {19, 28}, {20, 28}, {20, 29},
                {20, 30}, {19, 30}, {18, 30}, {17, 30}, {16, 30}};
  }

  std::list<std::pair<int, int>> body1_0;
  std::list<std::pair<int, int>> body9_4;
  std::list<std::pair<int, int>> body12_3;
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

TEST_F(SnakeTest, MoveOneStep) {
  gamestatus::Snake snake_right_1_0(body1_0, gamestatus::Direction::RIGHT);
  gamestatus::Snake snake_right_9_4(body9_4, gamestatus::Direction::RIGHT);

  gamestatus::Snake snake_left_1_0(body1_0, gamestatus::Direction::LEFT);
  gamestatus::Snake snake_left_9_4(body9_4, gamestatus::Direction::LEFT);

  gamestatus::Snake snake_up_1_0(body1_0, gamestatus::Direction::UP);
  gamestatus::Snake snake_up_9_4(body9_4, gamestatus::Direction::UP);

  gamestatus::Snake snake_down_1_0(body1_0, gamestatus::Direction::DOWN);
  gamestatus::Snake snake_down_9_4(body9_4, gamestatus::Direction::DOWN);

  std::list<std::pair<int, int>> expected_right_1_0 = {{21, 30}};
  std::list<std::pair<int, int>> expected_right_9_4 = {
      {21, 30}, {20, 30}, {19, 30}, {19, 29}, {18, 29},
      {17, 29}, {17, 28}, {17, 27}, {16, 27}};

  std::list<std::pair<int, int>> expected_left_1_0 = {{19, 30}};
  std::list<std::pair<int, int>> expected_left_9_4 = {
      {19, 30}, {20, 30}, {19, 30}, {19, 29}, {18, 29},
      {17, 29}, {17, 28}, {17, 27}, {16, 27}};

  std::list<std::pair<int, int>> expected_up_1_0 = {{20, 31}};
  std::list<std::pair<int, int>> expected_up_9_4 = {
      {20, 31}, {20, 30}, {19, 30}, {19, 29}, {18, 29},
      {17, 29}, {17, 28}, {17, 27}, {16, 27}};

  std::list<std::pair<int, int>> expected_down_1_0 = {{20, 29}};
  std::list<std::pair<int, int>> expected_down_9_4 = {
      {20, 29}, {20, 30}, {19, 30}, {19, 29}, {18, 29},
      {17, 29}, {17, 28}, {17, 27}, {16, 27}};

  snake_right_1_0.move();
  snake_right_9_4.move();

  snake_left_1_0.move();
  snake_left_9_4.move();

  snake_up_1_0.move();
  snake_up_9_4.move();

  snake_down_1_0.move();
  snake_down_9_4.move();

  EXPECT_EQ(snake_right_1_0.getBody(), expected_right_1_0);
  EXPECT_EQ(snake_right_9_4.getBody(), expected_right_9_4);

  EXPECT_EQ(snake_left_1_0.getBody(), expected_left_1_0);
  EXPECT_EQ(snake_left_9_4.getBody(), expected_left_9_4);

  EXPECT_EQ(snake_up_1_0.getBody(), expected_up_1_0);
  EXPECT_EQ(snake_up_9_4.getBody(), expected_up_9_4);

  EXPECT_EQ(snake_down_1_0.getBody(), expected_down_1_0);
  EXPECT_EQ(snake_down_9_4.getBody(), expected_down_9_4);
}

TEST_F(SnakeTest, EatFood) {
  std::pair<int, int> food = {21, 30};
  std::list<std::pair<int, int>> expected1_0 = {{21, 30}, {20, 30}};
  std::list<std::pair<int, int>> expected9_4 = {
      {21, 30}, {20, 30}, {19, 30}, {19, 29}, {18, 29},
      {17, 29}, {17, 28}, {17, 27}, {16, 27}, {15, 27}};

  gamestatus::Snake snake1_0(body1_0, gamestatus::Direction::RIGHT);
  gamestatus::Snake snake9_4(body9_4, gamestatus::Direction::RIGHT);

  snake1_0.eatFood(food);
  snake9_4.eatFood(food);

  EXPECT_EQ(snake1_0.getBody(), expected1_0);
  EXPECT_EQ(snake9_4.getBody(), expected9_4);
}

TEST_F(ToolsTest, GenerateFood) {
  int map_width = 500;
  int map_height = 500;
  std::pair<int, int> food = gamestatus::generateFood(
      body9_4, map_width,
      map_height);  // Assuming map_width = 500, map_height = 500
  EXPECT_THAT(food.first,
              testing::AllOf(testing::Ge(1), testing::Le(map_width)));
  EXPECT_THAT(food.second,
              testing::AllOf(testing::Ge(1), testing::Le(map_height)));
}

TEST_F(SnakeTest, DeadSnake) {
  gamestatus::Snake snake12_3(body12_3, gamestatus::Direction::UP);

  snake12_3.move();
  std::cout << "Head of snae12_3 is: (" << snake12_3.getBody().front().first
            << ", " << snake12_3.getBody().front().second << ").\n";
  EXPECT_EQ(snake12_3.deadSnake(), 1);
}