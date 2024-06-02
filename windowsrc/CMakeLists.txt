cmake_minimum_required(VERSION 3.29)
project(gamewindow VERSION 1.0)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

cmake_policy(SET CMP0135 NEW)

set(SOURCE_FILES gamewindow.cpp)

add_executable(gamewindow ${SOURCE_FILES})

target_include_directories(gamewindow PRIVATE ${SDL_INCLUDE_DIR})
target_link_directories(gamewindow PRIVATE ${SDL_BUILD_DIR})
target_link_libraries(gamewindow PRIVATE SDL3::SDL3-shared)

enable_testing()