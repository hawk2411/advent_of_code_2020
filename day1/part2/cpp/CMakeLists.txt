cmake_minimum_required(VERSION 3.19)

set(CMAKE_CXX_STANDARD 20)

configure_file(../../input_data.txt ${CMAKE_BINARY_DIR}/day1/part2/cpp/input_data.txt)
add_executable(day1_part2 main.cpp)