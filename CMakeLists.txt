project(usb-notifier CXX)

cmake_minimum_required(VERSION 2.8.12)

add_definitions(-DVERSION_MAJOR=0)
add_definitions(-DVERSION_MINOR=0)
add_definitions(-DVERSION_PATCH=1)

find_package(Qt5 COMPONENTS Core)

# find_package(usb REQUIRED)

set(CMAKE_AUTOMOC TRUE)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# C++11
add_definitions("-std=gnu++11")

# src
add_subdirectory(src)
add_subdirectory(example)
