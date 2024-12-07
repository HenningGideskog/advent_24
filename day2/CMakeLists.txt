# Specify the source files and day number
set(DAY_NUMBER 2)

add_executable(day${DAY_NUMBER}_part1 part1.cc)
target_link_libraries(day${DAY_NUMBER}_part1 PRIVATE aoclib)
add_executable(day${DAY_NUMBER}_part2 part2.cc)
target_link_libraries(day${DAY_NUMBER}_part2 PRIVATE aoclib)

set(INPUT_NAME input_${DAY_NUMBER}.txt)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/${INPUT_NAME} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
