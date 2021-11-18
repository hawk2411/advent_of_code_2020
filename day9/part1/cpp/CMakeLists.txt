cmake_minimum_required(VERSION 3.17)
project(day9)

set(day_nr 9)
set(part_nr 1)

set(target_name day${day_nr}_part${part_nr})
configure_file(../../input_data.txt ${CMAKE_BINARY_DIR}/day${day_nr}/part${part_nr}/cpp/input_data.txt)

add_executable(${target_name} main.cpp StringTools.cpp StringTools.h)
