cmake_minimum_required(VERSION 3.29)
project(gamewindow VERSION 1.0)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

cmake_policy(SET CMP0135 NEW)

set(SOURCE_FILES snakegame.cpp)

add_executable(snakegame ${SOURCE_FILES})

target_include_directories(snakegame PRIVATE ${SDL_INCLUDE_DIR})
target_include_directories(snakegame PRIVATE ${CMAKE_SOURCE_DIR}/snakesrc)

target_link_libraries(snakegame PRIVATE gamestatus)
target_link_libraries(snakegame PRIVATE SDL3::SDL3-shared)

enable_testing()