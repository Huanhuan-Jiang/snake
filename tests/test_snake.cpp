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
      {0, 1}, {1, 1}, {1, 2}};  // first element y <= 0, beyond the map
  std::deque<std::pair<int, int>> illegaldeque7 = {
      {0, 0}, {1, 1}, {1, 2}};  // first x <= 0, beyond the map
  std::deque<std::pair<int, int>> illegaldeque8 = {
      {499, 499},
      {499, 500},
      {498, 500}};  // intermediate element y >= 500, beyond the map
  std::deque<std::pair<int, int>> illegaldeque9 = {
      {499, 499},
      {500, 499},
      {500, 498}};  // intermediate element x >= 500, beyond the map
  std::deque<std::pair<int, int>> illegaldeque10 = {
      {1, 1}, {1, 0}, {2, 0}};  // intermediate element y <= 0, beyond the map
  std::deque<std::pair<int, int>> illegaldeque11 = {
      {1, 1}, {0, 1}, {0, 2}};  // intermediate x <= 0, beyond the map

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
  gamestatus::DequeOfUniquePairs<int, int> body9({{20, 30},
                                                  {19, 30},
                                                  {19, 29},
                                                  {18, 29},
                                                  {17, 29},
                                                  {17, 28},
                                                  {17, 27},
                                                  {16, 27},
                                                  {15, 27}});

  gamestatus::Snake snake9_right(body9, gamestatus::Direction::RIGHT);
  gamestatus::Snake snake9_left(body9, gamestatus::Direction::LEFT);
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
  gamestatus::Snake snake_down_4(body4, gamestatus::Direction::DOWN);
  gamestatus::Snake snake_up_8(body8, gamestatus::Direction::UP);

  gamestatus::DequeOfUniquePairs<int, int> expected_left_4(
      {{17, 27}, {18, 27}, {18, 28}, {18, 29}});
  gamestatus::DequeOfUniquePairs<int, int> expected_right_4(
      {{19, 27}, {18, 27}, {18, 28}, {18, 29}});
  gamestatus::DequeOfUniquePairs<int, int> expected_down_4(
      {{18, 26}, {18, 27}, {18, 28}, {18, 29}});
  gamestatus::DequeOfUniquePairs<int, int> expected_up_8({{18, 29},
                                                          {18, 28},
                                                          {18, 27},
                                                          {19, 27},
                                                          {20, 27},
                                                          {20, 28},
                                                          {20, 29},
                                                          {19, 29}});

  std::pair<int, int> food = {100, 100};

  EXPECT_EQ(snake_left_4.moveOrEat(food), gamestatus::MoveState::MOVE);
  EXPECT_EQ(snake_right_4.moveOrEat(food), gamestatus::MoveState::MOVE);
  EXPECT_EQ(snake_down_4.moveOrEat(food), gamestatus::MoveState::MOVE);
  EXPECT_EQ(snake_up_8.moveOrEat(food), gamestatus::MoveState::MOVE);

  EXPECT_EQ(snake_left_4.getBody(), expected_left_4);
  EXPECT_EQ(snake_right_4.getBody(), expected_right_4);
  EXPECT_EQ(snake_down_4.getBody(), expected_down_4);
  EXPECT_EQ(snake_up_8.getBody(), expected_up_8);
}

TEST(SnakeTest, MoveOneStepThenHitWall) {
  std::pair<int, int> food = {100, 100};

  gamestatus::DequeOfUniquePairs<int, int> body_up(
      {{499, 499}, {499, 498}, {498, 498}, {498, 497}});
  gamestatus::Snake snake_up(body_up, gamestatus::Direction::UP, 500, 500);

  gamestatus::DequeOfUniquePairs<int, int> body_down(
      {{1, 1}, {1, 2}, {2, 2}, {2, 3}});
  gamestatus::Snake snake_down(body_down, gamestatus::Direction::DOWN, 500,
                               500);

  gamestatus::DequeOfUniquePairs<int, int> body_left(
      {{1, 3}, {1, 4}, {2, 4}, {3, 4}});
  gamestatus::Snake snake_left(body_left, gamestatus::Direction::LEFT, 500,
                               500);

  gamestatus::DequeOfUniquePairs<int, int> body_right(
      {{499, 496}, {499, 497}, {499, 498}, {498, 498}});
  gamestatus::Snake snake_right(body_right, gamestatus::Direction::RIGHT, 500,
                                500);

  EXPECT_EQ(snake_up.moveOrEat(food), gamestatus::MoveState::DIE);
  EXPECT_EQ(snake_down.moveOrEat(food), gamestatus::MoveState::DIE);
  EXPECT_EQ(snake_left.moveOrEat(food), gamestatus::MoveState::DIE);
  EXPECT_EQ(snake_right.moveOrEat(food), gamestatus::MoveState::DIE);
}

TEST(SnakeTest, EatFood) {
  gamestatus::DequeOfUniquePairs<int, int> body9({{20, 30},
                                                  {19, 30},
                                                  {19, 29},
                                                  {18, 29},
                                                  {17, 29},
                                                  {17, 28},
                                                  {17, 27},
                                                  {16, 27},
                                                  {15, 27}});

  std::pair<int, int> food = {21, 30};

  gamestatus::DequeOfUniquePairs<int, int> expected9({{21, 30},
                                                      {20, 30},
                                                      {19, 30},
                                                      {19, 29},
                                                      {18, 29},
                                                      {17, 29},
                                                      {17, 28},
                                                      {17, 27},
                                                      {16, 27},
                                                      {15, 27}});

  gamestatus::Snake snake9(body9);

  EXPECT_EQ(snake9.moveOrEat(food), gamestatus::MoveState::EAT);
  EXPECT_EQ(snake9.getBody(), expected9);
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
  gamestatus::Snake snake1(body1, gamestatus::Direction::UP);
  EXPECT_EQ(snake1.moveOrEat({100, 100}), gamestatus::MoveState::DIE);
}

TEST(ToolsTest, UpdateDirection) {
  gamestatus::DequeOfUniquePairs<int, int> initial_body({{17, 30}, {16, 30}});
  gamestatus::Snake snake(initial_body);

  // From RIGHT
  EXPECT_EQ(snake.updateDirection(gamestatus::Direction::RIGHT),
            gamestatus::Direction::RIGHT);
  EXPECT_EQ(snake.updateDirection(gamestatus::Direction::LEFT),
            gamestatus::Direction::RIGHT);
  EXPECT_EQ(snake.updateDirection(gamestatus::Direction::UP),
            gamestatus::Direction::UP);
  snake.updateDirection(gamestatus::Direction::RIGHT);
  EXPECT_EQ(snake.updateDirection(gamestatus::Direction::DOWN),
            gamestatus::Direction::DOWN);

  // From DOWN
  EXPECT_EQ(snake.updateDirection(gamestatus::Direction::DOWN),
            gamestatus::Direction::DOWN);
  EXPECT_EQ(snake.updateDirection(gamestatus::Direction::UP),
            gamestatus::Direction::DOWN);
  EXPECT_EQ(snake.updateDirection(gamestatus::Direction::RIGHT),
            gamestatus::Direction::RIGHT);
  snake.updateDirection(gamestatus::Direction::DOWN);
  EXPECT_EQ(snake.updateDirection(gamestatus::Direction::LEFT),
            gamestatus::Direction::LEFT);

  // From LEFT
  EXPECT_EQ(snake.updateDirection(gamestatus::Direction::LEFT),
            gamestatus::Direction::LEFT);
  EXPECT_EQ(snake.updateDirection(gamestatus::Direction::RIGHT),
            gamestatus::Direction::LEFT);
  EXPECT_EQ(snake.updateDirection(gamestatus::Direction::DOWN),
            gamestatus::Direction::DOWN);
  snake.updateDirection(gamestatus::Direction::LEFT);
  EXPECT_EQ(snake.updateDirection(gamestatus::Direction::UP),
            gamestatus::Direction::UP);

  // From UP
  EXPECT_EQ(snake.updateDirection(gamestatus::Direction::UP),
            gamestatus::Direction::UP);
  EXPECT_EQ(snake.updateDirection(gamestatus::Direction::DOWN),
            gamestatus::Direction::UP);
  EXPECT_EQ(snake.updateDirection(gamestatus::Direction::LEFT),
            gamestatus::Direction::LEFT);
  snake.updateDirection(gamestatus::Direction::UP);
  EXPECT_EQ(snake.updateDirection(gamestatus::Direction::RIGHT),
            gamestatus::Direction::RIGHT);
}

TEST(CycleTest, FromBirthToDeath) {
  gamestatus::DequeOfUniquePairs<int, int> initial_body({{17, 30}});
  gamestatus::Snake snake(initial_body);

  std::vector<std::pair<int, int>> food_container = {
      {18, 30}, {19, 30}, {20, 30}, {20, 29},
      {20, 28}, {19, 28}, {18, 28}, {18, 29}};

  for (auto i = 0; i < food_container.size(); ++i) {
    std::pair<int, int> food = food_container[i];
    snake.moveOrEat(food);

    if (i == 2) {
      snake.updateDirection(gamestatus::Direction::DOWN);
    }
    if (i == 4) {
      snake.updateDirection(gamestatus::Direction::LEFT);
    }
    if (i == 6) {
      snake.updateDirection(gamestatus::Direction::UP);
    }
  }
  EXPECT_EQ(snake.moveOrEat({100, 100}), gamestatus::MoveState::DIE);
}
