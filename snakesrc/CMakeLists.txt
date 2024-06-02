add_library(gamestatus gamestatus.cpp)
target_include_directories(gamestatus INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(gamestatus PRIVATE ${SDL_INCLUDE_DIR})
target_link_libraries(gamestatus PRIVATE SDL3::SDL3-shared)
