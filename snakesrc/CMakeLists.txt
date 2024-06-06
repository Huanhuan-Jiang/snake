set(LIBRARY_NAME gamestatus)

set(SOURCE_FILES
    dequeofunique.h
    gamestatus.cpp
    gamestatus.h
)

add_library(${LIBRARY_NAME} ${SOURCE_FILES})

target_include_directories(${LIBRARY_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

