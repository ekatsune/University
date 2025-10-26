## 'Google_test' is the subproject name
#project(Google_tests)
#
## 'lib' is the folder with Google Test sources
#add_subdirectory(lib)
#include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
#
## 'Google_Tests_run' is the target name
## 'test1.cpp' are source files with tests
#add_executable(Google_Tests_run test1.cpp)
#target_link_libraries(Google_Tests_run gtest gtest_main)

cmake_minimum_required(VERSION 3.14)
project(GoogleTests)

# Добавляем GoogleTest из поддиректории
add_subdirectory(lib)

# Создаём исполняемый файл тестов
add_executable(MyTests test1.cpp   ../Tape.cpp
        ../Rule.cpp
        ../Machine.cpp)

# Подключаем include-пути из GoogleTest
target_include_directories(MyTests PRIVATE
        lib/googletest/include
        lib/googlemock/include
        ../             # чтобы видеть Play.h
)

# Линкуем библиотеки GoogleTest
target_link_libraries(MyTests gtest gtest_main)

# Разрешаем CTest запускать тесты
enable_testing()
add_test(NAME MyTests COMMAND MyTests)