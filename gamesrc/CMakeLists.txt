cmake_minimum_required(VERSION 3.29)
project(snakegame VERSION 1.0)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

cmake_policy(SET CMP0135 NEW)

#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

set(SOURCE_FILES snakegame.cpp)

add_subdirectory(../snakesrc snakesrc)
add_subdirectory(../thirdparty/googletest thirdparty/googletest)
add_subdirectory(../thirdparty/SDL thirdparty/SDL)

include_directories(${SDL_INCLUDE_DIR})

set(SDL_SOURCE_DIR ${CMAKE_SOURCE_DIR}/../thirdparty/SDL CACHE PATH "Path to SDL source directory")
set(SDL_BUILD_DIR ${SDL_SOURCE_DIR}/build CACHE PATH "Path to SDL build directory")
set(SDL_INCLUDE_DIR ${SDL_SOURCE_DIR}/include CACHE PATH "Path to SDL include directory")
set(SDL_LIBRARY ${SDL_BUILD_DIR}/libSDL3.dylib CACHE FILEPATH "Path to SDL library")

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

add_executable(snakegame ${SOURCE_FILES})

target_include_directories(snakegame INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(snakegame PRIVATE ${CMAKE_SOURCE_DIR}/../snakesrc)

#target_include_directories(snakegame PRIVATE ${SDL_INCLUDE_DIR})

target_link_libraries(snakegame PRIVATE gamestatus)
target_link_libraries(snakegame PRIVATE SDL3::SDL3-shared)

enable_testing()