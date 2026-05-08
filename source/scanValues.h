#pragma once
#include <iostream>
#include <limits>

inline void flushInput() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

inline bool scanInt(int& out) {
    if (std::cin >> out) return true;
    std::cout << "  Введите целое число!" << std::endl;
    flushInput();
    return false;
}

inline int inputSize() {
    int n;
    std::cout << "  Размер: ";
    while (!scanInt(n) || n <= 0) {
        std::cout << "  Целое положительное число: ";
    }
    return n;
}

template <class T>
bool scanValue(T& out);

template <> inline bool scanValue<int>(int& out) { return scanInt(out); }

template <> inline bool scanValue<bool>(bool& out) {
    int x;
    if (!scanInt(x)) return false;
    if (x != 0 && x != 1) {
        std::cout << "  Введите 0 или 1!" << std::endl;
        return false;
    }
    out = (x == 1);
    return true;
}