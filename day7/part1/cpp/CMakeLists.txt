cmake_minimum_required(VERSION 3.17)
project(day7)

set(CMAKE_CXX_STANDARD 14)

set(day_nr 7)
set(part_nr 1)

set(target_name day${day_nr}_part${part_nr})
configure_file(../../input_data.txt ${CMAKE_BINARY_DIR}/day${day_nr}/part${part_nr}/cpp/input_data.txt)

add_executable(${target_name} main.cpp)
