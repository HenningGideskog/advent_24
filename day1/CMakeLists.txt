# Specify the source files and day number
set(DAY_NUMBER 1)

add_executable(day${DAY_NUMBER}_part1 part1.cc)
add_executable(day${DAY_NUMBER}_part2 part2.cc)

set(INPUT_NAME input_${DAY_NUMBER}.txt)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/${INPUT_NAME} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
