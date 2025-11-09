
cmake_minimum_required(VERSION 3.14)
project(GoogleTests)

enable_testing()

# Добавляем GoogleTest из поддиректории
add_subdirectory(lib)

# Создаём исполняемый файл тестов
add_executable(MyTests ../test1.cpp ../Play.cpp)

# Подключаем include-пути из GoogleTest
target_include_directories(MyTests PRIVATE
        lib/googletest/include
        lib/googlemock/include
        ../             # чтобы видеть Play.h
)

# Линкуем библиотеки GoogleTest
target_link_libraries(MyTests gtest gtest_main)

add_test(NAME MyTests COMMAND MyTests)