#define DEBUG_MODE

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <deque>
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
  std::deque<std::pair<int, int>> illegaldeque1;  // empty body
  std::deque<std::pair<int, int>> illegaldeque2 = {
      {20, 30}, {19, 30}, {19, 29}, {18, 28}, {17, 29},
      {17, 28}, {17, 27}, {16, 27}, {15, 27}};  // not continuous
  std::deque<std::pair<int, int>> illegaldeque3 = {
      {20, 30}, {19, 30}, {19, 29}, {17, 28}, {17, 29}};  // not continuous
  std::deque<std::pair<int, int>> illegaldeque4 = {
      {499, 500},
      {499, 499},
      {499, 498}};  // first element y >= 500, beyond the map
  std::deque<std::pair<int, int>> illegaldeque5 = {
      {500, 499},
      {499, 499},
      {499, 498}};  // first element x >= 500, beyond the map
  std::deque<std::pair<int, int>> illegaldeque6 = {
      {-1, 0}, {0, 0}, {0, 1}};  // first element x < 0, beyond the map
  std::deque<std::pair<int, int>> illegaldeque7 = {
      {0, -1}, {0, 0}, {0, 1}};  // first y < 0, beyond the map
  std::deque<std::pair<int, int>> illegaldeque8 = {
      {499, 499},
      {499, 500},
      {498, 500}};  // intermediate element y >= 500, beyond the map
  std::deque<std::pair<int, int>> illegaldeque9 = {
      {499, 499},
      {500, 499},
      {500, 498}};  // intermediate element x >= 500, beyond the map
  std::deque<std::pair<int, int>> illegaldeque10 = {
      {0, 0}, {-1, 0}, {-1, 1}};  // intermediate element x < 0, beyond the map
  std::deque<std::pair<int, int>> illegaldeque11 = {
      {0, 0}, {0, -1}, {1, -1}};  // intermediate y < 0, beyond the map

  std::vector<std::pair<gamestatus::DequeOfUniquePairs<int, int>, std::string>>
      illegal_cases = {
          {gamestatus::DequeOfUniquePairs<int, int>(illegaldeque1),
           "Snake body is empty!"},
          {gamestatus::DequeOfUniquePairs<int, int>(illegaldeque2),
           "Snake body is not continuous!"},
          {gamestatus::DequeOfUniquePairs<int, int>(illegaldeque3),
           "Snake body is not continuous!"},
          {gamestatus::DequeOfUniquePairs<int, int>(illegaldeque4),
           "Snake body is beyond the map!"},
          {gamestatus::DequeOfUniquePairs<int, int>(illegaldeque5),
           "Snake body is beyond the map!"},
          {gamestatus::DequeOfUniquePairs<int, int>(illegaldeque6),
           "Snake body is beyond the map!"},
          {gamestatus::DequeOfUniquePairs<int, int>(illegaldeque7),
           "Snake body is beyond the map!"},
          {gamestatus::DequeOfUniquePairs<int, int>(illegaldeque8),
           "Snake body is beyond the map!"},
          {gamestatus::DequeOfUniquePairs<int, int>(illegaldeque9),
           "Snake body is beyond the map!"},
          {gamestatus::DequeOfUniquePairs<int, int>(illegaldeque10),
           "Snake body is beyond the map!"},
          {gamestatus::DequeOfUniquePairs<int, int>(illegaldeque11),
           "Snake body is beyond the map!"}};

  for (auto& [illegalbody, error_message] : illegal_cases) {
    EXPECT_THAT(
        [&illegalbody]() {
          gamestatus::Snake illegalsnake(
              illegalbody, gamestatus::Direction::RIGHT, 500, 500);
        },
        Throws<std::runtime_error>(
            Property(&std::runtime_error::what, HasSubstr(error_message))));
  }

  gamestatus::DequeOfUniquePairs<int, int> illegalbody12(
      {{20, 19}, {20, 20}, {20, 21}});  // deduced_dir = up
  EXPECT_THAT(
      [&illegalbody12]() {
        gamestatus::Snake illegalsnake12(illegalbody12,
                                         gamestatus::Direction::DOWN, 500, 500);
      },
      Throws<std::runtime_error>(
          Property(&std::runtime_error::what,
                   HasSubstr("The head direction is invalid!"))));

  gamestatus::DequeOfUniquePairs<int, int> illegalbody13(
      {{20, 19}, {20, 18}, {20, 17}});  // deduced_dir = down
  EXPECT_THAT(
      [&illegalbody13]() {
        gamestatus::Snake illegalsnake13(illegalbody13,
                                         gamestatus::Direction::UP, 500, 500);
      },
      Throws<std::runtime_error>(
          Property(&std::runtime_error::what,
                   HasSubstr("The head direction is invalid!"))));

  gamestatus::DequeOfUniquePairs<int, int> illegalbody14(
      {{20, 19}, {21, 19}, {22, 19}});  // deduced_dir = left
  EXPECT_THAT(
      [&illegalbody14]() {
        gamestatus::Snake illegalsnake14(
            illegalbody14, gamestatus::Direction::RIGHT, 500, 500);
      },
      Throws<std::runtime_error>(
          Property(&std::runtime_error::what,
                   HasSubstr("The head direction is invalid!"))));

  gamestatus::DequeOfUniquePairs<int, int> illegalbody15(
      {{20, 19}, {19, 19}, {18, 19}});  // deduced_dir = right
  EXPECT_THAT(
      [&illegalbody15]() {
        gamestatus::Snake illegalsnake15(illegalbody15,
                                         gamestatus::Direction::LEFT, 500, 500);
      },
      Throws<std::runtime_error>(
          Property(&std::runtime_error::what,
                   HasSubstr("The head direction is invalid!"))));
}

TEST(SnakeTest, GetSameFood) {
  gamestatus::DequeOfUniquePairs<int, int> body({{20, 30}});
  gamestatus::Snake snake1(body);
  gamestatus::Snake snake2(body);
  EXPECT_NE(snake1.getFood(), snake2.getFood());
}

TEST(SnakeTest, SnakeSize) {
  gamestatus::DequeOfUniquePairs<int, int> body1({{20, 30}});  // one unit long
  gamestatus::DequeOfUniquePairs<int, int> body9({{20, 30},
                                                  {19, 30},
                                                  {19, 29},
                                                  {18, 29},
                                                  {17, 29},
                                                  {17, 28},
                                                  {17, 27},
                                                  {16, 27},
                                                  {15, 27}});
  gamestatus::Snake snake1(body1);
  gamestatus::Snake snake9(body9);

  EXPECT_EQ(snake1.size(), 1u);
  EXPECT_EQ(snake9.size(), 9u);
}

TEST(SnakeTest, GetDirection) {
  gamestatus::DequeOfUniquePairs<int, int> body8(
      {{19, 30},
       {19, 29},
       {18, 29},
       {17, 29},
       {17, 28},
       {17, 27},
       {16, 27},
       {15, 27}});  // deduced_dir = down

  gamestatus::DequeOfUniquePairs<int, int> body9(
      {{20, 30},
       {19, 30},
       {19, 29},
       {18, 29},
       {17, 29},
       {17, 28},
       {17, 27},
       {16, 27},
       {15, 27}});  // deduced_dir = right

  gamestatus::Snake snake9_right(body9);
  gamestatus::Snake snake9_left(body8, gamestatus::Direction::LEFT);
  gamestatus::Snake snake9_up(body9, gamestatus::Direction::UP);
  gamestatus::Snake snake9_down(body9, gamestatus::Direction::DOWN);

  EXPECT_EQ(snake9_right.getDirection(), gamestatus::Direction::RIGHT);
  EXPECT_EQ(snake9_left.getDirection(), gamestatus::Direction::LEFT);
  EXPECT_EQ(snake9_up.getDirection(), gamestatus::Direction::UP);
  EXPECT_EQ(snake9_down.getDirection(), gamestatus::Direction::DOWN);
}

TEST(SnakeTest, GetCustomerizedBody) {
  gamestatus::DequeOfUniquePairs<int, int> body1({{20, 30}});  // one unit long
  gamestatus::DequeOfUniquePairs<int, int> body9({{20, 30},
                                                  {19, 30},
                                                  {19, 29},
                                                  {18, 29},
                                                  {17, 29},
                                                  {17, 28},
                                                  {17, 27},
                                                  {16, 27},
                                                  {15, 27}});
  gamestatus::Snake snake1(body1);
  gamestatus::Snake snake9(body9);

  EXPECT_EQ(snake1.getBody(), body1);
  EXPECT_EQ(snake9.getBody(), body9);
}

TEST(SnakeTest, GetDefaultBody) {
  gamestatus::Snake snake1(50, 50);
  gamestatus::DequeOfUniquePairs<int, int> expect_body1(
      {{25, 25}, {24, 25}, {23, 25}});

  EXPECT_EQ(snake1.getBody(), expect_body1);
  EXPECT_EQ(snake1.getDirection(), gamestatus::Direction::RIGHT);

  gamestatus::Snake snake2(100, 100);
  gamestatus::DequeOfUniquePairs<int, int> expect_body2(
      {{50, 50}, {49, 50}, {48, 50}});

  EXPECT_EQ(snake2.getBody(), expect_body2);
  EXPECT_EQ(snake2.getDirection(), gamestatus::Direction::RIGHT);
}

TEST(SnakeTest, MoveOneStep) {
  gamestatus::DequeOfUniquePairs<int, int> body4(
      {{18, 27}, {18, 28}, {18, 29}, {19, 29}});
  gamestatus::DequeOfUniquePairs<int, int> body8(
      {{18, 28},
       {18, 27},
       {19, 27},
       {20, 27},
       {20, 28},
       {20, 29},
       {19, 29},
       {18, 29}});  // Snake almost hit the body;

  gamestatus::Snake snake_left_4(body4, gamestatus::Direction::LEFT);
  gamestatus::Snake snake_right_4(body4, gamestatus::Direction::RIGHT);
  gamestatus::Snake snake_up_4(body4, gamestatus::Direction::UP);
  gamestatus::Snake snake_down_8(body8, gamestatus::Direction::DOWN);

  gamestatus::DequeOfUniquePairs<int, int> expected_left_4(
      {{17, 27}, {18, 27}, {18, 28}, {18, 29}});
  gamestatus::DequeOfUniquePairs<int, int> expected_right_4(
      {{19, 27}, {18, 27}, {18, 28}, {18, 29}});
  gamestatus::DequeOfUniquePairs<int, int> expected_up_4(
      {{18, 26}, {18, 27}, {18, 28}, {18, 29}});
  gamestatus::DequeOfUniquePairs<int, int> expected_down_8({{18, 29},
                                                            {18, 28},
                                                            {18, 27},
                                                            {19, 27},
                                                            {20, 27},
                                                            {20, 28},
                                                            {20, 29},
                                                            {19, 29}});

  EXPECT_EQ(snake_left_4.next(), gamestatus::NextState::MOVE);
  EXPECT_EQ(snake_right_4.next(), gamestatus::NextState::MOVE);
  EXPECT_EQ(snake_up_4.next(), gamestatus::NextState::MOVE);
  EXPECT_EQ(snake_down_8.next(), gamestatus::NextState::MOVE);

  EXPECT_EQ(snake_left_4.getBody(), expected_left_4);
  EXPECT_EQ(snake_right_4.getBody(), expected_right_4);
  EXPECT_EQ(snake_up_4.getBody(), expected_up_4);
  EXPECT_EQ(snake_down_8.getBody(), expected_down_8);
}

TEST(SnakeTest, MoveOneStepThenHitWall) {
  gamestatus::DequeOfUniquePairs<int, int> body_up(
      {{1, 0}, {1, 1}, {1, 2}, {2, 2}, {2, 3}});
  gamestatus::Snake snake_up(body_up, gamestatus::Direction::UP, 500, 500);

  gamestatus::DequeOfUniquePairs<int, int> body_down(
      {{499, 499}, {499, 498}, {498, 498}, {498, 497}});
  gamestatus::Snake snake_down(body_down, gamestatus::Direction::DOWN, 500,
                               500);

  gamestatus::DequeOfUniquePairs<int, int> body_left(
      {{0, 2}, {1, 2}, {2, 2}, {3, 2}});
  gamestatus::Snake snake_left(body_left, gamestatus::Direction::LEFT, 500,
                               500);

  gamestatus::DequeOfUniquePairs<int, int> body_right(
      {{499, 496}, {499, 497}, {499, 498}, {498, 498}});
  gamestatus::Snake snake_right(body_right, gamestatus::Direction::RIGHT, 500,
                                500);

  EXPECT_EQ(snake_up.next(), gamestatus::NextState::DIE);
  EXPECT_EQ(snake_down.next(), gamestatus::NextState::DIE);
  EXPECT_EQ(snake_left.next(), gamestatus::NextState::DIE);
  EXPECT_EQ(snake_right.next(), gamestatus::NextState::DIE);
}

TEST(SnakeTest, EatFood) {
  gamestatus::DequeOfUniquePairs<int, int> body(
      {{45, 44}, {44, 44}, {43, 44}, {43, 43}, {43, 42}});

  gamestatus::DequeOfUniquePairs<int, int> expected(
      {{46, 44}, {45, 44}, {44, 44}, {43, 44}, {43, 43}, {43, 42}});

  gamestatus::Snake snake(body, gamestatus::Direction::RIGHT, 50, 50, 12345);

  EXPECT_EQ(snake.next(), gamestatus::NextState::EAT);
  EXPECT_EQ(snake.getBody(), expected);
}

TEST(CycleTest, EatFoodThenDie) {
  gamestatus::DequeOfUniquePairs<int, int> body(
      {{45, 44}, {44, 44}, {43, 44}, {42, 44}, {41, 44}, {40, 44}});

  auto map_w = 50;
  auto map_h = 50;
  int seed = 12345;
  gamestatus::Snake snake(body, gamestatus::Direction::RIGHT, map_w, map_h,
                          seed);

  snake.next();
  snake.newDirection(gamestatus::Direction::DOWN);
  snake.next();
  snake.next();
  snake.newDirection(gamestatus::Direction::LEFT);
  snake.next();
  snake.newDirection(gamestatus::Direction::UP);
  snake.next();
  EXPECT_EQ(snake.next(), gamestatus::NextState::DIE);
}

TEST(SnakeTest, MoveOneStepThenHitBody) {
  gamestatus::DequeOfUniquePairs<int, int> body1({{18, 29},
                                                  {18, 28},
                                                  {19, 28},
                                                  {20, 28},
                                                  {20, 29},
                                                  {20, 30},
                                                  {19, 30},
                                                  {18, 30},
                                                  {17, 30},
                                                  {16, 30}});
  gamestatus::Snake snake1(body1, gamestatus::Direction::DOWN);
  EXPECT_EQ(snake1.next(), gamestatus::NextState::DIE);
}

TEST(ToolsTest, newDirection) {
  // From UP
  gamestatus::DequeOfUniquePairs<int, int> body1(
      {{17, 30}, {17, 31}});  // deduced_dir is up
  gamestatus::Snake snake1(body1, gamestatus::Direction::UP);
  EXPECT_EQ(snake1.newDirection(gamestatus::Direction::UP),
            gamestatus::Direction::UP);
  EXPECT_EQ(snake1.newDirection(gamestatus::Direction::DOWN),
            gamestatus::Direction::UP);
  EXPECT_EQ(snake1.newDirection(gamestatus::Direction::LEFT),
            gamestatus::Direction::LEFT);
  EXPECT_EQ(snake1.newDirection(gamestatus::Direction::RIGHT),
            gamestatus::Direction::RIGHT);

  // From DOWN
  gamestatus::DequeOfUniquePairs<int, int> body2(
      {{17, 30}, {17, 29}});  // deduced_dir is down
  gamestatus::Snake snake2(body2, gamestatus::Direction::DOWN);
  EXPECT_EQ(snake2.newDirection(gamestatus::Direction::DOWN),
            gamestatus::Direction::DOWN);
  EXPECT_EQ(snake2.newDirection(gamestatus::Direction::UP),
            gamestatus::Direction::DOWN);
  EXPECT_EQ(snake2.newDirection(gamestatus::Direction::RIGHT),
            gamestatus::Direction::RIGHT);
  EXPECT_EQ(snake2.newDirection(gamestatus::Direction::LEFT),
            gamestatus::Direction::LEFT);

  // From LEFT
  gamestatus::DequeOfUniquePairs<int, int> body3(
      {{17, 30}, {18, 30}});  // deduced_dir is left
  gamestatus::Snake snake3(body3, gamestatus::Direction::LEFT);
  EXPECT_EQ(snake3.newDirection(gamestatus::Direction::LEFT),
            gamestatus::Direction::LEFT);
  EXPECT_EQ(snake3.newDirection(gamestatus::Direction::RIGHT),
            gamestatus::Direction::LEFT);
  EXPECT_EQ(snake3.newDirection(gamestatus::Direction::DOWN),
            gamestatus::Direction::DOWN);
  EXPECT_EQ(snake3.newDirection(gamestatus::Direction::UP),
            gamestatus::Direction::UP);

  // From RIGHT
  gamestatus::DequeOfUniquePairs<int, int> body4(
      {{17, 30}, {16, 30}});  // deduced_dir = right
  gamestatus::Snake snake4(body4);
  EXPECT_EQ(snake4.newDirection(gamestatus::Direction::RIGHT),
            gamestatus::Direction::RIGHT);
  EXPECT_EQ(snake4.newDirection(gamestatus::Direction::LEFT),
            gamestatus::Direction::RIGHT);
  EXPECT_EQ(snake4.newDirection(gamestatus::Direction::UP),
            gamestatus::Direction::UP);
  EXPECT_EQ(snake4.newDirection(gamestatus::Direction::DOWN),
            gamestatus::Direction::DOWN);
}

TEST(ToolsTest, GenerateFoodWithCustomizedSeed) {
  gamestatus::DequeOfUniquePairs<int, int> body(
      {{18, 29}, {18, 28}, {19, 28}, {20, 28}, {20, 29}, {20, 30}});

  auto map_w = 50;
  auto map_h = 50;
  int seed = 12345;

  gamestatus::Snake snake(body, gamestatus::Direction::RIGHT, map_w, map_h,
                          seed);
  auto food = snake.getFood();

  EXPECT_THAT(food.first, testing::AllOf(testing::Gt(0), testing::Lt(map_w)));
  EXPECT_THAT(food.second, testing::AllOf(testing::Gt(0), testing::Lt(map_w)));
  EXPECT_THAT(snake.getBody().set().find(food), snake.getBody().set().end());
}

TEST(ToolsTest, GenerateFoodWithDefaultSeed) {
  gamestatus::DequeOfUniquePairs<int, int> body(
      {{18, 29}, {18, 28}, {19, 28}, {20, 28}, {20, 29}, {20, 30}});

  auto map_w = 50;
  auto map_h = 50;

  gamestatus::Snake snake(body, gamestatus::Direction::RIGHT, map_w, map_h);
  auto food = snake.getFood();

  EXPECT_THAT(food.first, testing::AllOf(testing::Gt(0), testing::Lt(map_w)));
  EXPECT_THAT(food.second, testing::AllOf(testing::Gt(0), testing::Lt(map_w)));
  EXPECT_THAT(snake.getBody().set().find(food), snake.getBody().set().end());
}

TEST(ToolsTest, GenerateMultipleFoodWithCustomizedSeed) {
  gamestatus::DequeOfUniquePairs<int, int> body(
      {{18, 29}, {18, 28}, {19, 28}, {20, 28}, {20, 29}, {20, 30}});

  auto map_w = 50;
  auto map_h = 50;
  auto seed = 12345;

  gamestatus::Snake snake(body, gamestatus::Direction::RIGHT, map_w, map_h,
                          seed);

  for (auto i = 0; i < 10; ++i) {
    snake.generateFood();
    auto food = snake.getFood();

    EXPECT_THAT(food.first, testing::AllOf(testing::Gt(0), testing::Lt(map_w)));
    EXPECT_THAT(food.second,
                testing::AllOf(testing::Gt(0), testing::Lt(map_w)));
    EXPECT_THAT(snake.getBody().set().find(food), snake.getBody().set().end());
  }
}

TEST(ToolsTest, GenerateMultipleFoodWithDefaultSeed) {
  gamestatus::DequeOfUniquePairs<int, int> body(
      {{18, 29}, {18, 28}, {19, 28}, {20, 28}, {20, 29}, {20, 30}});

  auto map_w = 50;
  auto map_h = 50;

  gamestatus::Snake snake(body, gamestatus::Direction::RIGHT, map_w, map_h);

  for (auto i = 0; i < 10; ++i) {
    snake.generateFood();
    auto food = snake.getFood();

    EXPECT_THAT(food.first, testing::AllOf(testing::Gt(0), testing::Lt(map_w)));
    EXPECT_THAT(food.second,
                testing::AllOf(testing::Gt(0), testing::Lt(map_w)));
    EXPECT_THAT(snake.getBody().set().find(food), snake.getBody().set().end());
  }
}
