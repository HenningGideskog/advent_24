cmake_minimum_required(VERSION 3.10)

project(AdventOfCode_2024)

# Enable C++20 standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add compile flags for warning
add_compile_options(-Wall -Wextra -Wpedantic)

add_subdirectory(utils)

# Add subdirectory for individual days
add_subdirectory(day1)
