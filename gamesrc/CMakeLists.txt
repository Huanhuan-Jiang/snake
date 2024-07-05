cmake_minimum_required(VERSION 3.29)
project(try VERSION 1.0)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

cmake_policy(SET CMP0135 NEW)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Bin)

set(SOURCE_FILES try.cpp)

add_subdirectory(../thirdparty/SDL thirdparty/SDL)

include_directories(${SDL_INCLUDE_DIR})

set(SDL_SOURCE_DIR ${CMAKE_SOURCE_DIR}/../thirdparty/SDL CACHE PATH "Path to SDL source directory")
set(SDL_BUILD_DIR ${CMAKE_CURRENT_SOURCE_DIR}/build CACHE PATH "Path to SDL build directory")
set(SDL_INCLUDE_DIR ${SDL_SOURCE_DIR}/include CACHE PATH "Path to SDL include directory")
set(SDL_LIBRARY ${SDL_BUILD_DIR}/thirdparty/SDL/libSDL3.so CACHE FILEPATH "Path to SDL library")

# Build SDL libraries
if(NOT EXISTS ${SDL_BUILD_DIR}/CMakeCache.txt)
    message(STATUS "Configuring SDL...")
    execute_process(
        COMMAND ${CMAKE_COMMAND} -S${SDL_SOURCE_DIR} -B${SDL_BUILD_DIR}
    )
    execute_process(
        COMMAND ${CMAKE_COMMAND} --build ${SDL_BUILD_DIR}
    )
endif()

add_executable(try ${SOURCE_FILES})

target_include_directories(try INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(try PRIVATE SDL3::SDL3-shared)
target_link_libraries(try PRIVATE ${SDL_LIBRARY})