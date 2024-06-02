cmake_minimum_required(VERSION 3.29)
project(snaketest VERSION 1.0)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

cmake_policy(SET CMP0135 NEW)

set(GOOGLETEST_VERSION "1.14.0" CACHE STRING "Version of Google Test")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(snakesrc)
add_subdirectory(windowsrc)
add_subdirectory(thirdparty/googletest)
add_subdirectory(thirdparty/SDL)

set(SDL_SOURCE_DIR ${CMAKE_SOURCE_DIR}/thirdparty/SDL)
set(SDL_BUILD_DIR ${SDL_SOURCE_DIR}/build)
set(SDL_INCLUDE_DIR ${SDL_SOURCE_DIR}/include)
set(SDL_LIBRARY ${SDL_BUILD_DIR}/libSDL3.dylib)

# Ensure that SDL is built with CMake
if(NOT EXISTS ${SDL_BUILD_DIR}/CMakeCache.txt)
    message(STATUS "Configuring SDL...")
    execute_process(
        COMMAND ${CMAKE_COMMAND} -S${SDL_SOURCE_DIR} -B${SDL_BUILD_DIR}
    )
    execute_process(
        COMMAND ${CMAKE_COMMAND} --build ${SDL_BUILD_DIR}
    )
endif()

add_executable(snaketest tests/test_snake.cpp)
add_executable(dequeofuniquetest tests/test_dequeofunique.cpp)

target_link_libraries(snaketest PRIVATE 
    GTest::gtest_main 
    GTest::gmock_main
)

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
