cmake_minimum_required(VERSION 3.29)
project(snaketest VERSION 1.0)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

cmake_policy(SET CMP0135 NEW)

set(GOOGLETEST_VERSION "1.14.0" CACHE STRING "Version of Google Test")

add_subdirectory(snakesrc)
add_subdirectory(thirdparty/googletest)
add_subdirectory(thirdparty/yaml-cpp)

add_executable(snaketest tests/test_snake.cpp)
add_executable(dequeofuniquetest tests/test_dequeofunique.cpp)

# is it redudant?
target_include_directories(snaketest PRIVATE thirdparty/yaml-cpp/include)

target_link_libraries(snaketest PRIVATE 
    GTest::gtest_main 
    GTest::gmock_main
)

target_link_libraries(snaketest PRIVATE yaml-cpp)

target_link_libraries(dequeofuniquetest PRIVATE 
    GTest::gtest_main 
    GTest::gmock_main
)

target_link_libraries(snaketest PRIVATE gamestatus)
target_link_libraries(dequeofuniquetest PRIVATE gamestatus)

enable_testing()

include(GoogleTest)
gtest_discover_tests(snaketest)
gtest_discover_tests(dequeofuniquetest)
