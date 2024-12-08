# Specify the source files and day number
set(DAY_NUMBER 3)

add_executable(day${DAY_NUMBER} day${DAY_NUMBER}.cc)
target_link_libraries(day${DAY_NUMBER} PRIVATE aoclib)

set(INPUT_NAME input_${DAY_NUMBER}.txt)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/${INPUT_NAME} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
