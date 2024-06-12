#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <yaml-cpp/yaml.h>

#include <deque>
#include <fstream>
#include <iostream>
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
      {499, 499},
      {499, 500},
      {498, 500}};  // intermediate element y >= 500, beyond the map
  std::deque<std::pair<int, int>> illegaldeque6 = {
      {500, 499},
      {499, 499},
      {499, 498}};  // first element x >= 500, beyond the map
  std::deque<std::pair<int, int>> illegaldeque7 = {
      {499, 499},
      {500, 499},
      {500, 498}};  // intermediate element x >= 500, beyond the map
  std::deque<std::pair<int, int>> illegaldeque8 = {
      {0, 1}, {1, 1}, {1, 2}};  // first element y <= 0, beyond the map
  std::deque<std::pair<int, int>> illegaldeque9 = {
      {1, 1}, {1, 0}, {2, 0}};  // intermediate element y <= 0, beyond the map
  std::deque<std::pair<int, int>> illegaldeque10 = {
      {0, 0}, {1, 1}, {1, 2}};  // first x <= 0, beyond the map
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

  for (const auto& [illegalbody, error_message] : illegal_cases) {
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
  gamestatus::Snake snake1(body1);
  gamestatus::Snake snake9(body9);

  EXPECT_EQ(snake1.getBody(), body1);
  EXPECT_EQ(snake9.getBody(), body9);
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

  gamestatus::Snake snake_up_9(body9, gamestatus::Direction::UP);
  gamestatus::Snake snake_down_9(body9, gamestatus::Direction::DOWN);
  gamestatus::Snake snake_right_9(body9, gamestatus::Direction::RIGHT);
  gamestatus::Snake snake_left_7(body7, gamestatus::Direction::LEFT);

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
  gamestatus::DequeOfUniquePairs<int, int> expected_right_9({{21, 30},
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

  EXPECT_EQ(snake_up_9.moveOrEat(food), gamestatus::SnakeState::MOVE);
  EXPECT_EQ(snake_down_9.moveOrEat(food), gamestatus::SnakeState::MOVE);
  EXPECT_EQ(snake_right_9.moveOrEat(food), gamestatus::SnakeState::MOVE);
  EXPECT_EQ(snake_left_7.moveOrEat(food), gamestatus::SnakeState::MOVE);

  EXPECT_EQ(snake_up_9.getBody(), expected_up_9);
  EXPECT_EQ(snake_down_9.getBody(), expected_down_9);
  EXPECT_EQ(snake_right_9.getBody(), expected_right_9);
  EXPECT_EQ(snake_left_7.getBody(), expected_left_7);
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

  EXPECT_EQ(snake_up.moveOrEat(food), gamestatus::SnakeState::DIE);
  EXPECT_EQ(snake_down.moveOrEat(food), gamestatus::SnakeState::DIE);
  EXPECT_EQ(snake_left.moveOrEat(food), gamestatus::SnakeState::DIE);
  EXPECT_EQ(snake_right.moveOrEat(food), gamestatus::SnakeState::DIE);
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

  EXPECT_EQ(snake9.moveOrEat(food), gamestatus::SnakeState::EAT);
  EXPECT_EQ(snake9.getBody(), expected9);
}

TEST(SnakeTest, MoveOneStepThenHitBody) {
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
  gamestatus::Snake snake10(body10, gamestatus::Direction::UP);
  EXPECT_EQ(snake10.moveOrEat({100, 100}), gamestatus::SnakeState::DIE);
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

TEST(ToolsTest, GenerateFoodWithCustomizedSeed) {
  gamestatus::DequeOfUniquePairs<int, int> body(
      {{18, 29}, {18, 28}, {19, 28}, {20, 28}, {20, 29}, {20, 30}});

  auto map_w = 50;
  auto map_h = 50;
  int seed = 12345;

  gamestatus::Snake snake(body, gamestatus::Direction::RIGHT, map_w, map_h,
                          seed);
  auto food = snake.generateFood();

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
  auto food = snake.generateFood();

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
    auto food = snake.generateFood();

    EXPECT_THAT(food.first, testing::AllOf(testing::Gt(0), testing::Lt(map_w)));
    EXPECT_THAT(food.second,
                testing::AllOf(testing::Gt(0), testing::Lt(map_w)));
    EXPECT_THAT(snake.getBody().set().find(food), snake.getBody().set().end());
  }
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
  EXPECT_EQ(snake.moveOrEat({100, 100}), gamestatus::SnakeState::DIE);
}

TEST(CycleTest, EatRandomFoodAndDie) {
  gamestatus::DequeOfUniquePairs<int, int> body(
      {{45, 44}, {44, 44}, {43, 44}, {42, 44}, {41, 44}, {40, 44}});

  auto map_w = 50;
  auto map_h = 50;
  int seed = 12345;
  gamestatus::Snake snake(body, gamestatus::Direction::RIGHT, map_w, map_h,
                          seed);

  auto food = snake.generateFood();

  snake.moveOrEat(food);
  snake.updateDirection(gamestatus::Direction::DOWN);
  snake.moveOrEat(food);
  snake.moveOrEat(food);
  snake.updateDirection(gamestatus::Direction::LEFT);
  snake.moveOrEat(food);
  snake.updateDirection(gamestatus::Direction::UP);
  snake.moveOrEat(food);
  EXPECT_EQ(snake.moveOrEat({100, 100}), gamestatus::SnakeState::DIE);
}

TEST(CycleTest, MimicASimpleGame) {
  gamestatus::DequeOfUniquePairs<int, int> body(
      {{45, 44}, {44, 44}, {43, 44}, {42, 44}, {41, 44}, {40, 44}});

  auto map_w = 50;
  auto map_h = 50;

  std::string filename = "../tests/a_simple_input.yml";
  YAML::Node user_input = YAML::LoadFile(filename);

  auto seed = user_input["seed"]["value"].as<int>();
  gamestatus::Snake snake(body, gamestatus::Direction::RIGHT, map_w, map_h,
                          seed);

  auto food = snake.generateFood();
  auto snake_state = gamestatus::SnakeState::MOVE;

  for (const auto& key_node : user_input["keys"]) {
    auto value = key_node["value"].as<std::string>();

    if (value == "up") {
      snake.updateDirection(gamestatus::Direction::UP);
    } else if (value == "down") {
      snake.updateDirection(gamestatus::Direction::DOWN);
    } else if (value == "left") {
      snake.updateDirection(gamestatus::Direction::LEFT);
    } else if (value == "right") {
      snake.updateDirection(gamestatus::Direction::RIGHT);
    }
    snake_state = snake.moveOrEat(food);
  }
  EXPECT_EQ(snake_state, gamestatus::SnakeState::DIE);
}

TEST(CycleTest, MimicASimpleGameWithDefaultBody) {
  gamestatus::DequeOfUniquePairs<int, int> default_init_body =
      gamestatus::initBody();

  auto map_w = 50;
  auto map_h = 50;

  std::string filename = "../tests/a_simple_input_with_default_body.yml";
  YAML::Node user_input = YAML::LoadFile(filename);

  auto seed = user_input["seed"]["value"].as<int>();
  gamestatus::Snake snake(default_init_body, gamestatus::Direction::RIGHT,
                          map_w, map_h, seed);

  auto food = snake.generateFood();
  auto snake_state = gamestatus::SnakeState::MOVE;

  for (const auto& key_node : user_input["keys"]) {
    auto value = key_node["value"].as<std::string>();

    if (value == "up") {
      snake.updateDirection(gamestatus::Direction::UP);
    } else if (value == "down") {
      snake.updateDirection(gamestatus::Direction::DOWN);
    } else if (value == "left") {
      snake.updateDirection(gamestatus::Direction::LEFT);
    } else if (value == "right") {
      snake.updateDirection(gamestatus::Direction::RIGHT);
    }
    snake_state = snake.moveOrEat(food);
  }
  EXPECT_EQ(snake_state, gamestatus::SnakeState::EAT);
}
