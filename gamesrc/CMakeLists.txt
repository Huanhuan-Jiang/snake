cmake_minimum_required(VERSION 3.29)
project(gamewindow VERSION 1.0)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

cmake_policy(SET CMP0135 NEW)

set(SOURCE_FILES snakegame.cpp)

#include_directories(${CMAKE_SOURCE_DIR}/snakesrc)
#include_directories(${SDL_INCLUDE_DIR})

add_executable(snakegame ${SOURCE_FILES})

target_include_directories(snakegame PRIVATE ${SDL_INCLUDE_DIR})
target_include_directories(snakegame PRIVATE ${CMAKE_SOURCE_DIR}/snakesrc)

target_link_libraries(snakegame PRIVATE gamestatus)
target_link_libraries(snakegame PRIVATE SDL3::SDL3-shared)

# 输出 snakegame.cpp 编译目录的绝对路径
message(STATUS "snakegame.cpp 编译目录: ${CMAKE_CURRENT_BINARY_DIR}")

# 输出 snakesrc 目录的绝对路径
message(STATUS "snakesrc 目录: ${CMAKE_SOURCE_DIR}/snakesrc")

# 输出 gamestatus.h 头文件路径
set(GAMESTATUS_HEADER ${CMAKE_SOURCE_DIR}/snakesrc/gamestatus.h)
message(STATUS "gamestatus.h 头文件路径: ${GAMESTATUS_HEADER}")


enable_testing()