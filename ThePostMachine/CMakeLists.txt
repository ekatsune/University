cmake_minimum_required(VERSION 3.30)
project(ThePostMachine)

set(CMAKE_CXX_STANDARD 20)

add_executable(ThePostMachine main.cpp Tape.cpp Rule.cpp Machine.cpp)

add_subdirectory(Google_tests)

if (CMAKE_COMPILER_IS_GNUCXX)
    message(STATUS "Enabling GCC coverage flags")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0 --coverage")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage")
endif()