cmake_minimum_required(VERSION 4.2)
project(Laba_2_sv)

set(CMAKE_CXX_STANDARD 11)

# Основная программа
add_executable(main source/main.cpp
        headers/Exception.h
        headers/DynamicArray.h
        headers/LinkedList.h
        headers/Option.h
        headers/Sequence.h
        headers/ArraySequence.h
        headers/MutableArraySequence.h
        headers/ImmutableArraySequence.h
        headers/BitSequence.h
        headers/ListSequence.h
)

# Тесты
add_executable(tests tests/tests.cpp
        headers/Exception.h
        headers/DynamicArray.h
        tests/testsDynamicArray.cpp
        headers/LinkedList.h
        tests/testsLinkedList.cpp
        headers/Option.h
        headers/Sequence.h
        headers/ArraySequence.h
        tests/testsArraySequence.cpp
        headers/MutableArraySequence.h
        headers/ImmutableArraySequence.h
        headers/BitSequence.h
        tests/testsBitSequence.cpp
        headers/ListSequence.h)
