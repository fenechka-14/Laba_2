cmake_minimum_required(VERSION 4.2)
project(Laba_2_sv)

set(CMAKE_CXX_STANDARD 11)

# Основная программа
add_executable(main source/main.cpp
        headers/Exception.h
        headers/Dynamic_Array.h
        headers/Linked_List.h
        headers/Option.h
        headers/Sequence.h
        headers/Array_Sequence.h
)

# Тесты
add_executable(tests tests/tests.cpp
        headers/Exception.h
        headers/Dynamic_Array.h
        tests/tests_Dynamic_Array.cpp
        headers/Linked_List.h
        tests/tests_Linked_List.cpp
        headers/Option.h
        headers/Sequence.h
        headers/Array_Sequence.h)
