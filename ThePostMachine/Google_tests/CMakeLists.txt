
cmake_minimum_required(VERSION 3.14)
project(GoogleTests)

add_subdirectory(lib)

add_executable(MyTests test1.cpp   ../Tape.cpp
        ../Rule.cpp
        ../Machine.cpp)

target_include_directories(MyTests PRIVATE
        lib/googletest/include
        lib/googlemock/include
        ../
)

target_link_libraries(MyTests gtest gtest_main)

enable_testing()
add_test(NAME MyTests COMMAND MyTests)