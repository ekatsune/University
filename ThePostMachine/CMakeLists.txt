cmake_minimum_required(VERSION 3.30)
project(ThePostMachine)

set(CMAKE_CXX_STANDARD 20)

add_executable(ThePostMachine main.cpp Tape.cpp Rule.cpp Machine.cpp)
