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
  gamestatus::DequeOfUniquePairs<int, int> body9({{20, 30},
                                                  {19, 30},
                                                  {19, 29},
                                                  {18, 29},
                                                  {17, 29},
                                                  {17, 28},
                                                  {17, 27},
                                                  {16, 27},
                                                  {15, 27}});
  gamestatus::Snake snake1(body1, gamestatus::Direction::RIGHT);
  gamestatus::Snake snake9(body9, gamestatus::Direction::RIGHT);

  EXPECT_EQ(snake1.size(), 1u);
  EXPECT_EQ(snake9.size(), 9u);
}

TEST(SnakeTest, GetBody) {
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
  gamestatus::Snake snake1(body1, gamestatus::Direction::RIGHT);
  gamestatus::Snake snake9(body9, gamestatus::Direction::RIGHT);

  EXPECT_EQ(snake1.getBody().deque(), body1.deque());
  EXPECT_EQ(snake9.getBody().deque(), body9.deque());
  EXPECT_EQ(snake1.getBody().set(), body1.set());
  EXPECT_EQ(snake9.getBody().set(), body9.set());
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

TEST(SnakeTest, MoveOneStep) {
  gamestatus::DequeOfUniquePairs<int, int> body7(
      {{18, 30}, {18, 29}, {17, 29}, {17, 28}, {17, 27}, {16, 27}, {15, 27}});

  gamestatus::DequeOfUniquePairs<int, int> body9({{20, 30},
                                                  {19, 30},
                                                  {19, 29},
                                                  {18, 29},
                                                  {17, 29},
                                                  {17, 28},
                                                  {17, 27},
                                                  {16, 27},
                                                  {15, 27}});

  gamestatus::Snake snake_right_9(body9, gamestatus::Direction::RIGHT);
  gamestatus::Snake snake_up_9(body9, gamestatus::Direction::UP);
  gamestatus::Snake snake_down_9(body9, gamestatus::Direction::DOWN);

  gamestatus::Snake snake_left_7(body7, gamestatus::Direction::LEFT);

  gamestatus::DequeOfUniquePairs<int, int> expected_right_9({{21, 30},
                                                             {20, 30},
                                                             {19, 30},
                                                             {19, 29},
                                                             {18, 29},
                                                             {17, 29},
                                                             {17, 28},
                                                             {17, 27},
                                                             {16, 27}});

  gamestatus::DequeOfUniquePairs<int, int> expected_up_9({{20, 31},
                                                          {20, 30},
                                                          {19, 30},
                                                          {19, 29},
                                                          {18, 29},
                                                          {17, 29},
                                                          {17, 28},
                                                          {17, 27},
                                                          {16, 27}});

  gamestatus::DequeOfUniquePairs<int, int> expected_down_9({{20, 29},
                                                            {20, 30},
                                                            {19, 30},
                                                            {19, 29},
                                                            {18, 29},
                                                            {17, 29},
                                                            {17, 28},
                                                            {17, 27},
                                                            {16, 27}});

  gamestatus::DequeOfUniquePairs<int, int> expected_left_7(
      {{17, 30}, {18, 30}, {18, 29}, {17, 29}, {17, 28}, {17, 27}, {16, 27}});

  std::pair<int, int> food = {100, 100};

  snake_right_9.moveOrEat(food);
  snake_up_9.moveOrEat(food);
  snake_down_9.moveOrEat(food);
  snake_left_7.moveOrEat(food);

  EXPECT_EQ(snake_right_9.getBody().deque(), expected_right_9.deque());
  EXPECT_EQ(snake_up_9.getBody().deque(), expected_up_9.deque());
  EXPECT_EQ(snake_down_9.getBody().deque(), expected_down_9.deque());
  EXPECT_EQ(snake_left_7.getBody().deque(), expected_left_7.deque());
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

  gamestatus::Snake snake9(body9, gamestatus::Direction::RIGHT);

  snake9.moveOrEat(food);

  EXPECT_EQ(snake9.getBody().deque(), expected9.deque());
}

TEST(SnakeTest, DeadSnake) {
  gamestatus::DequeOfUniquePairs<int, int> body12({{18, 29},
                                                   {18, 28},
                                                   {19, 28},
                                                   {20, 28},
                                                   {20, 29},
                                                   {20, 30},
                                                   {19, 30},
                                                   {18, 30},
                                                   {17, 30},
                                                   {16, 30}});
  gamestatus::Snake snake12(body12, gamestatus::Direction::UP);
  snake12.moveOrEat({100, 100});
  EXPECT_EQ(snake12.deadSnake(), false);
}

TEST(CycleTest, FromBirthToDeath) {
  gamestatus::DequeOfUniquePairs<int, int> initial_body({{17, 30}});
  gamestatus::Snake snake(initial_body, gamestatus::Direction::RIGHT);

  std::vector<std::pair<int, int>> food_container = {
      {18, 30}, {19, 30}, {20, 30}, {20, 29},
      {20, 28}, {19, 28}, {18, 28}, {18, 29}};

  for (auto i = 0; i < food_container.size(); ++i) {
    std::pair<int, int> food = food_container[i];
    snake.moveOrEat(food_container[i]);

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
  EXPECT_EQ(snake.deadSnake(), false);
}

TEST(UpdateTest, UpdateDirection) {
  gamestatus::DequeOfUniquePairs<int, int> initial_body({{17, 30}, {16, 30}});
  gamestatus::Snake snake(initial_body, gamestatus::Direction::RIGHT);

  snake.updateDirection(gamestatus::Direction::UP);
  EXPECT_EQ(snake.getDirection(), gamestatus::Direction::UP);

  snake.updateDirection(gamestatus::Direction::LEFT);
  EXPECT_EQ(snake.getDirection(), gamestatus::Direction::LEFT);

  snake.updateDirection(gamestatus::Direction::DOWN);
  EXPECT_EQ(snake.getDirection(), gamestatus::Direction::DOWN);

  snake.updateDirection(gamestatus::Direction::RIGHT);
  EXPECT_EQ(snake.getDirection(), gamestatus::Direction::RIGHT);
}
