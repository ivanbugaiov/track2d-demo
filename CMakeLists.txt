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
  set(CMAKE_BUILD_TYPE Release)
endif()

add_subdirectory(track2d-lib)

add_executable(track2d-demo
    src/file_plot_source.cpp
    src/main.cpp
    src/polygon_perimeter.cpp
    src/track2d_demo_utils.cpp)

target_include_directories(track2d-demo PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(track2d-demo track2d)
