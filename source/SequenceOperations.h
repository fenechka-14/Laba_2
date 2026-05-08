#pragma once
#include <iostream>
#include "../headers/MutableArraySequence.h"
#include "../headers/ImmutableArraySequence.h"
#include "../headers/MutableListSequence.h"
#include "../headers/ImmutableListSequence.h"
#include "../headers/BitSequence.h"
#include "scanValues.h"
#include "menu.h"

// Функции для Map/Where/Reduce
template <class T> T fSquare(const T& x) { return x * x; }
template <class T> T fNegate(const T& x) { return -x; }
template <class T> bool fPositive(const T& x) { return x > 0; }
template <class T> T fSum(const T& a, const T& b) { return a + b; }
template <class T> T fMul(const T& a, const T& b) { return a * b; }
inline bool fNot(const bool& x) { return !x; }
inline bool fIsTrue(const bool& x) { return x; }
inline bool fAnd(const bool& a, const bool& b) { return a && b; }
inline bool fOr(const bool& a, const bool& b) { return a || b; }

// Чтение массива
template <class T>
T* readValues(int n) {
    T* temp = new T[n];
    for (int i = 0; i < n; ++i) {
        std::cout << "  Элемент [" << i << "]: ";
        while (!scanValue<T>(temp[i]))
            std::cout << "  Элемент [" << i << "]: ";
    }
    return temp;
}

// Создание Sequence
template <class T>
Sequence<T>* makeSequence(int family, int mutability, T* items, int n) {
    if (family == 1) {
        if (mutability == 1) return new MutableArraySequence<T>(items, n);
        else                 return new ImmutableArraySequence<T>(items, n);
    } else {
        if (mutability == 1) return new MutableListSequence<T>(items, n);
        else                 return new ImmutableListSequence<T>(items, n);
    }
}

template <class T>
Sequence<T>* createSequence() {
    int family, mutability;
    do { printFamilyMenu(); } while (!scanInt(family) || family < 1 || family > 2);
    do { printMutabilityMenu(); } while (!scanInt(mutability) || mutability < 1 || mutability > 2);
    int n = inputSize();
    T* temp = readValues<T>(n);
    Sequence<T>* result = makeSequence<T>(family, mutability, temp, n);
    delete[] temp;
    return result;
}

// Печать Sequence
template <class T>
void printSequence(Sequence<T>* s) {
    if (!s) { std::cout << "(null)"; return; }
    std::cout << "[";
    for (int i = 0; i < s->GetLength(); ++i) {
        if (i > 0) std::cout << ", ";
        std::cout << s->Get(i);
    }
    std::cout << "]";
}

// Печать BitSequence
void printBitSequence(BitSequence* s) {
    if (!s) { std::cout << "(null)"; return; }
    std::cout << "[";
    for (int i = 0; i < s->GetLength(); ++i) {
        if (i > 0) std::cout << " ";
        std::cout << s->Get(i);
    }
    std::cout << "]";
}

// Append / Prepend / InsertAt
template <class T>
void modifySequence(Sequence<T>*& seq, const char* name) {
    if (!seq) { std::cout << "  Сначала создайте " << name << "!" << std::endl; return; }
    int op;
    do { printAddMenu(); } while (!scanInt(op) || op < 1 || op > 3);
    T value;
    std::cout << "  Значение: ";
    while (!scanValue<T>(value)) std::cout << "  Значение: ";
    Sequence<T>* old = seq;
    switch (op) {
        case 1: seq = seq->Append(value); break;
        case 2: seq = seq->Prepend(value); break;
        case 3: {
            int idx;
            std::cout << "  Индекс [0, " << seq->GetLength() << "]: ";
            while (!scanInt(idx) || idx < 0 || idx > seq->GetLength())
                std::cout << "  Индекс [0, " << seq->GetLength() << "]: ";
            seq = seq->InsertAt(value, idx);
            break;
        }
    }
    if (seq != old) delete old;
    std::cout << "  " << name << " = "; printSequence(seq); std::cout << std::endl;
}

// GetSubSequence
template <class T>
void subSequence(Sequence<T>* seq, const char* name) {
    if (!seq) { std::cout << "  Сначала создайте " << name << "!" << std::endl; return; }
    if (seq->GetLength() == 0) { std::cout << "  " << name << " пуст" << std::endl; return; }
    int max = seq->GetLength() - 1;
    int start, end;
    do { std::cout << "  start [0, " << max << "]: "; } while (!scanInt(start) || start < 0 || start > max);
    do { std::cout << "  end [" << start << ", " << max << "]: "; } while (!scanInt(end) || end < start || end > max);
    Sequence<T>* result = seq->GetSubSequence(start, end);
    std::cout << "  " << name << "[" << start << ".." << end << "] = ";
    printSequence(result); std::cout << std::endl;
    delete result;
}

// Map / Where / Reduce
template <class T>
void mapWhereReduce(Sequence<T>* seq, const char* name) {
    if (!seq) { std::cout << "  Сначала создайте " << name << "!" << std::endl; return; }
    int op;
    do { printMWRMenu(); } while (!scanInt(op) || op < 1 || op > 3);
    if (op == 1) {
        std::cout << "  1. x^2  2. -x  > ";
        int f; while (!scanInt(f) || f < 1 || f > 2) std::cout << "  > ";
        Sequence<T>* r = (f == 1) ? seq->Map(fSquare<T>) : seq->Map(fNegate<T>);
        std::cout << "  " << name << " = "; printSequence(r); std::cout << std::endl;
        delete r;
    } else if (op == 2) {
        std::cout << "  1. x > 0  > ";
        int f; while (!scanInt(f) || f != 1) std::cout << "  > ";
        Sequence<T>* r = seq->Where(fPositive<T>);
        std::cout << "  " << name << " = "; printSequence(r); std::cout << std::endl;
        delete r;
    } else {
        std::cout << "  1. sum  2. mul  > ";
        int f; while (!scanInt(f) || f < 1 || f > 2) std::cout << "  > ";
        T start;
        std::cout << "  Начальное значение: ";
        while (!scanValue<T>(start)) std::cout << "  Начальное значение: ";
        T r = (f == 1) ? seq->Reduce(fSum<T>, start) : seq->Reduce(fMul<T>, start);
        std::cout << "  Результат: " << r << std::endl;
    }
}

// Специализация для bool
template <>
inline void mapWhereReduce<bool>(Sequence<bool>* seq, const char* name) {
    if (!seq) { std::cout << "  Сначала создайте " << name << "!" << std::endl; return; }
    int op;
    do { printMWRMenu(); } while (!scanInt(op) || op < 1 || op > 3);
    if (op == 1) {
        Sequence<bool>* r = seq->Map(fNot);
        std::cout << "  NOT " << name << " = "; printSequence(r); std::cout << std::endl;
        delete r;
    } else if (op == 2) {
        Sequence<bool>* r = seq->Where(fIsTrue);
        std::cout << "  " << name << " (true) = "; printSequence(r); std::cout << std::endl;
        delete r;
    } else {
        std::cout << "  1. AND  2. OR  > ";
        int f; while (!scanInt(f) || f < 1 || f > 2) std::cout << "  > ";
        bool start;
        std::cout << "  Начальное (0/1): ";
        while (!scanValue<bool>(start)) std::cout << "  Начальное (0/1): ";
        bool r = (f == 1) ? seq->Reduce(fAnd, start) : seq->Reduce(fOr, start);
        std::cout << "  Результат: " << r << std::endl;
    }
}

// Главный цикл для int
template <class T>
void runMenu() {
    Sequence<T>* A = nullptr;
    Sequence<T>* B = nullptr;
    int choice;
    while (true) {
        printCommandMenu(false);
        if (!scanInt(choice)) continue;
        switch (choice) {
            case 1:
                delete A; A = createSequence<T>();
                std::cout << "  A = "; printSequence(A); std::cout << std::endl; break;
            case 2:
                delete B; B = createSequence<T>();
                std::cout << "  B = "; printSequence(B); std::cout << std::endl; break;
            case 3:
                std::cout << "  A = "; printSequence(A); std::cout << std::endl;
                std::cout << "  B = "; printSequence(B); std::cout << std::endl; break;
            case 4: {
                int who; do { printABMenu(); } while (!scanInt(who) || who < 1 || who > 2);
                modifySequence(who == 1 ? A : B, who == 1 ? "A" : "B"); break; }
            case 5:
                if (!A || !B) { std::cout << "  Создайте оба!" << std::endl; break; }
                { Sequence<T>* r = A->Concat(B);
                  std::cout << "  A + B = "; printSequence(r); std::cout << std::endl; break; }
            case 6: {
                int who; do { printABMenu(); } while (!scanInt(who) || who < 1 || who > 2);
                subSequence(who == 1 ? A : B, who == 1 ? "A" : "B"); break; }
            case 7: {
                int who; do { printABMenu(); } while (!scanInt(who) || who < 1 || who > 2);
                mapWhereReduce(who == 1 ? A : B, who == 1 ? "A" : "B"); break; }
            case 0: delete A; delete B; return;
            default: std::cout << "  Неверная команда" << std::endl; flushInput();
        }
    }
}

// Специализация для bool (с BitSequence)
template <>
inline void runMenu<bool>() {
    Sequence<bool>* A = nullptr;
    Sequence<bool>* B = nullptr;
    int choice;
    while (true) {
        printCommandMenu(true);
        if (!scanInt(choice)) continue;
        switch (choice) {
            case 1:
                delete A; A = createSequence<bool>();
                std::cout << "  A = "; printSequence(A); std::cout << std::endl; break;
            case 2:
                delete B; B = createSequence<bool>();
                std::cout << "  B = "; printSequence(B); std::cout << std::endl; break;
            case 3:
                std::cout << "  A = "; printSequence(A); std::cout << std::endl;
                std::cout << "  B = "; printSequence(B); std::cout << std::endl; break;
            case 4: {
                int who; do { printABMenu(); } while (!scanInt(who) || who < 1 || who > 2);
                modifySequence(who == 1 ? A : B, who == 1 ? "A" : "B"); break; }
            case 5:
                if (!A || !B) { std::cout << "  Создайте оба!" << std::endl; break; }
                { Sequence<bool>* r = A->Concat(B);
                  std::cout << "  A + B = "; printSequence(r); std::cout << std::endl; break; }
            case 6: {
                int who; do { printABMenu(); } while (!scanInt(who) || who < 1 || who > 2);
                subSequence(who == 1 ? A : B, who == 1 ? "A" : "B"); break; }
            case 7: {
                int who; do { printABMenu(); } while (!scanInt(who) || who < 1 || who > 2);
                mapWhereReduce<bool>(who == 1 ? A : B, who == 1 ? "A" : "B"); break; }
            case 8: {
                if (!A || !B) { std::cout << "  Создайте оба!" << std::endl; break; }
                BitSequence* bA = dynamic_cast<BitSequence*>(A);
                BitSequence* bB = dynamic_cast<BitSequence*>(B);
                if (!bA || !bB) { std::cout << "  Оба должны быть BitSequence (созданы через меню bool)" << std::endl; break; }
                int op; do { printBitOpMenu(); } while (!scanInt(op) || op < 1 || op > 4);
                if (op == 4) {
                    BitSequence r = bA->Not();
                    std::cout << "  NOT A = "; printBitSequence(&r); std::cout << std::endl;
                } else {
                    if (A->GetLength() != B->GetLength()) { std::cout << "  Длины разные!" << std::endl; break; }
                    BitSequence r = bA->And(*bB);
                    if (op == 2) r = bA->Or(*bB);
                    else if (op == 3) r = bA->Xor(*bB);
                    std::cout << "  Результат = "; printBitSequence(&r); std::cout << std::endl;
                }
                break;
            }
            case 0: delete A; delete B; return;
            default: std::cout << "  Неверная команда" << std::endl; flushInput();
        }
    }
}