cmake_minimum_required(VERSION 3.10)

project(AdventOfCode_2024)

# Enable C++20 standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add compile flags for warning
add_compile_options(-Wall -Wextra -Wpedantic -Ofast)

# Add subdirectory for individual days
add_subdirectory(day1)
add_subdirectory(day2)
add_subdirectory(day3)
add_subdirectory(day4)
add_subdirectory(day5)
add_subdirectory(day6)
add_subdirectory(day7)
