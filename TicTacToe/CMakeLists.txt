cmake_minimum_required(VERSION 3.14)
project(TicTacToe)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(TicTacToe main.cpp Play.cpp)

add_subdirectory(Google_tests)