cmake_minimum_required(VERSION 3.16)

project(
    track2d-demo
    VERSION 0.1.0
    LANGUAGES CXX
)

set(CMAKE_VERBOSE_MAKEFILE on)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif()

add_subdirectory(track2d-lib)

set(SOURCE_LIST     
    src/file_plot_source.cpp
    src/polygon_perimeter.cpp
    src/ppm_image.cpp
    src/track2d_demo_utils.cpp)

if(WITH_TRACK_DISPLAY)
    set(SOURCE_LIST ${SOURCE_LIST} src/track_display.cpp)
else()
    set(SOURCE_LIST ${SOURCE_LIST} src/track_display_stub.cpp)
endif()

add_executable(track2d-demo src/main.cpp ${SOURCE_LIST})

target_include_directories(track2d-demo PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(track2d-demo track2d)

add_executable(track2d-demo-test test/main.cpp ${SOURCE_LIST})
    
target_include_directories(track2d-demo-test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(track2d-demo-test track2d)
