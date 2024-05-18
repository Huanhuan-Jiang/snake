cmake_minimum_required(VERSION 3.14)
project(snaketest VERSION 1.0)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

cmake_policy(SET CMP0135 NEW)

# Define the version of Google Test being used
set(GOOGLETEST_VERSION "1.14.0" CACHE STRING "Version of Google Test")

# Add the subdirectory
add_subdirectory(snakesrc)
add_subdirectory(thirdparty/googletest)

# Add the executable for your test
add_executable(snaketest tests/test_snake.cpp)

# Include directories for executables
target_include_directories(snaketest PRIVATE snakesrc)
target_include_directories(snaketest PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/googletest/googletest/include/gtest
    ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/googletest/googlemock/include/gmock
) 

# Link test executables with Google Test
target_link_libraries(snaketest PRIVATE 
    GTest::gtest_main 
    GTest::gmock_main
)

# Link test executables with corresponding libraries
target_link_libraries(snaketest PRIVATE snakestatus)

# Link test executables with corresponding libraries
target_link_libraries(snaketest PRIVATE snakestatus)

# Enable C++14 standard
target_compile_features(snaketest PRIVATE cxx_std_14)

enable_testing()


include(GoogleTest)
gtest_discover_tests(snaketest)