#pragma once
#include <iostream>

inline void printBanner() {
    std::cout << std::endl;
    std::cout << "  ====== LAB 2: SEQUENCE ======" << std::endl;
    std::cout << std::endl;
}

inline void printTypeMenu() {
    std::cout << "  Выберите тип:" << std::endl;
    std::cout << "  1. int" << std::endl;
    std::cout << "  2. bool" << std::endl;
    std::cout << "  Тип: ";
}

inline void printFamilyMenu() {
    std::cout << "  Семейство:" << std::endl;
    std::cout << "  1. ArraySequence" << std::endl;
    std::cout << "  2. ListSequence" << std::endl;
    std::cout << "  Выбор: ";
}

inline void printMutabilityMenu() {
    std::cout << "  Изменяемость:" << std::endl;
    std::cout << "  1. Mutable" << std::endl;
    std::cout << "  2. Immutable" << std::endl;
    std::cout << "  Выбор: ";
}

inline void printCommandMenu(bool isBit) {
    std::cout << std::endl;
    std::cout << "  1. Создать A" << std::endl;
    std::cout << "  2. Создать B" << std::endl;
    std::cout << "  3. Показать A и B" << std::endl;
    std::cout << "  4. Append / Prepend / InsertAt" << std::endl;
    std::cout << "  5. Concat A + B" << std::endl;
    std::cout << "  6. GetSubSequence" << std::endl;
    std::cout << "  7. Map / Where / Reduce" << std::endl;
    if (isBit) {
        std::cout << "  8. AND / OR / XOR / NOT (bit)" << std::endl;
    }
    std::cout << "  0. Выход" << std::endl;
    std::cout << "  > ";
}

inline void printAddMenu() {
    std::cout << "  1. Append  2. Prepend  3. InsertAt" << std::endl;
    std::cout << "  Выбор: ";
}

inline void printMWRMenu() {
    std::cout << "  1. Map  2. Where  3. Reduce" << std::endl;
    std::cout << "  Выбор: ";
}

inline void printABMenu() {
    std::cout << "  1. A  2. B" << std::endl;
    std::cout << "  Выбор: ";
}

inline void printBitOpMenu() {
    std::cout << "  1. AND  2. OR  3. XOR  4. NOT" << std::endl;
    std::cout << "  Выбор: ";
}