# Specify the source files and day number
set(DAY_NUMBER 4)

add_executable(day${DAY_NUMBER} day${DAY_NUMBER}.cc)

set(INPUT_NAME input_${DAY_NUMBER}.txt)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/${INPUT_NAME} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
