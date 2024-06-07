#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <list>
#include <stdexcept>
#include <utility>
#include <vector>

#include "dequeofunique.h"
#include "gamestatus.h"

using testing::HasSubstr;
using testing::Property;
using testing::Throws;

class SnakeTest : public ::testing::Test {
 protected:
  void SetUp() override {
    gamestatus::DequeOfUniquePairs<int, int> body1_0({{20, 30}});  // one unit long
    gamestatus::DequeOfUniquePairs<int, int> body9_4({{20, 30}, {19, 30}, {19, 29}, {18, 29}, {17, 29},
               {17, 28}, {17, 27}, {16, 27}, {15, 27}});  // nine units long with
    // 4 turns
    gamestatus::DequeOfUniquePairs<int, int> body12_3({{18, 29}, {18, 28}, {19, 28}, {20, 28}, {20, 29},
                {20, 30}, {19, 30}, {18, 30}, {17, 30}, {16, 30}});
  }

  gamestatus::DequeOfUniquePairs<int, int> body1_0;
  gamestatus::DequeOfUniquePairs<int, int> body9_4;
  gamestatus::DequeOfUniquePairs<int, int> body12_3;
};
