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
using testing::Throws;
using testing::Property;

TEST(SnakeTest, SnakeThrowExceptionWithCorrectMessage) {
  std::deque<std::pair<int, int>> illegaldeque0;  // empty body
  std::deque<std::pair<int, int>> illegaldeque1 = {
      {20, 30}, {19, 30}, {19, 29}, {18, 28}, {17, 29},
      {17, 28}, {17, 27}, {16, 27}, {15, 27}};  // not continuous
  std::deque<std::pair<int, int>> illegaldeque2 = {
      {20, 30}, {19, 30}, {19, 29}, {17, 28}, {17, 29}};  // not continuous
  std::deque<std::pair<int, int>> illegaldeque3 = {
      {500, 501}, {499, 501}, {499, 500}};  // beyond the map

  std::vector<std::pair<gamestatus::DequeOfUniquePairs<int, int>, std::string>>
      illegal_cases = {{gamestatus::DequeOfUniquePairs<int, int>(illegaldeque0),
                        "Snake body is empty!"},
                       {gamestatus::DequeOfUniquePairs<int, int>(illegaldeque1),
                        "Snake body is not continuous!"},
                       {gamestatus::DequeOfUniquePairs<int, int>(illegaldeque2),
                        "Snake body is not continuous!"},
                       {gamestatus::DequeOfUniquePairs<int, int>(illegaldeque3),
                        "Snake body is beyond the map!"}};
  
  for (const auto& [illegalbody, error_message] : illegal_cases) {
    EXPECT_THAT(
        [&illegalbody]() {
          gamestatus::Snake illegalsnake(illegalbody,
                                         gamestatus::Direction::RIGHT, 500, 500);
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
  gamestatus::Snake snake1(body1, gamestatus::Direction::RIGHT, 500, 500);
  gamestatus::Snake snake9(body9, gamestatus::Direction::RIGHT, 500, 500);

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
  gamestatus::Snake snake1(body1, gamestatus::Direction::RIGHT, 500, 500);
  gamestatus::Snake snake9(body9, gamestatus::Direction::RIGHT, 500, 500);

  EXPECT_EQ(snake1.getBody(), body1);
  EXPECT_EQ(snake9.getBody(), body9);
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

  gamestatus::Snake snake9_right(body9, gamestatus::Direction::RIGHT, 500, 500);
  gamestatus::Snake snake9_left(body9, gamestatus::Direction::LEFT, 500, 500);
  gamestatus::Snake snake9_up(body9, gamestatus::Direction::UP, 500, 500);
  gamestatus::Snake snake9_down(body9, gamestatus::Direction::DOWN, 500, 500);

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

  gamestatus::Snake snake_right_9(body9, gamestatus::Direction::RIGHT,
                                  500, 500);
  gamestatus::Snake snake_up_9(body9, gamestatus::Direction::UP, 500, 500);
  gamestatus::Snake snake_down_9(body9, gamestatus::Direction::DOWN, 500, 500);

  gamestatus::Snake snake_left_7(body7, gamestatus::Direction::LEFT, 500, 500);

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

  EXPECT_EQ(snake_right_9.getBody(), expected_right_9);
  EXPECT_EQ(snake_up_9.getBody(), expected_up_9);
  EXPECT_EQ(snake_down_9.getBody(), expected_down_9);
  EXPECT_EQ(snake_left_7.getBody(), expected_left_7);
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

  gamestatus::Snake snake9(body9, gamestatus::Direction::RIGHT, 500, 500);

  snake9.moveOrEat(food);

  EXPECT_EQ(snake9.getBody(), expected9);
}

TEST(SnakeTest, DeadSnake) {
  gamestatus::DequeOfUniquePairs<int, int> body10({{18, 29},
                                                   {18, 28},
                                                   {19, 28},
                                                   {20, 28},
                                                   {20, 29},
                                                   {20, 30},
                                                   {19, 30},
                                                   {18, 30},
                                                   {17, 30},
                                                   {16, 30}});
  gamestatus::Snake snake10(body10, gamestatus::Direction::UP, 500, 500);
  EXPECT_EQ(snake10.moveOrEat({100, 100}), false);
}

TEST(UpdateTest, UpdateDirection) {
  gamestatus::DequeOfUniquePairs<int, int> initial_body({{17, 30}, {16, 30}});
  gamestatus::Snake snake(initial_body, gamestatus::Direction::RIGHT, 500, 500);

  snake.updateDirection(gamestatus::Direction::UP);
  EXPECT_EQ(snake.getDirection(), gamestatus::Direction::UP);

  snake.updateDirection(gamestatus::Direction::LEFT);
  EXPECT_EQ(snake.getDirection(), gamestatus::Direction::LEFT);

  snake.updateDirection(gamestatus::Direction::DOWN);
  EXPECT_EQ(snake.getDirection(), gamestatus::Direction::DOWN);

  snake.updateDirection(gamestatus::Direction::RIGHT);
  EXPECT_EQ(snake.getDirection(), gamestatus::Direction::RIGHT);
}

TEST(CycleTest, FromBirthToDeath) {
  gamestatus::DequeOfUniquePairs<int, int> initial_body({{17, 30}});
  gamestatus::Snake snake(initial_body, gamestatus::Direction::RIGHT, 500, 500);

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
  EXPECT_EQ(snake.moveOrEat({100, 100}), false);
}
