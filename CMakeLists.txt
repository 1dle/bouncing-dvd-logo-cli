cmake_minimum_required(VERSION 3.10.2)

set (CMAKE_CXX_STANDARD 11)

project(BouncingDvd)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

add_executable(BouncingDvd src/main.cpp)
target_link_libraries(BouncingDvd ${CURSES_LIBRARIES})
