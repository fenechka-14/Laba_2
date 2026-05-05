#pragma once

#include "LinkedList.h"
#include "Sequence.h"

template <typename T>
class ListSequence : public Sequence<T> {
    protected:
        LinkedList<T> items;
    public:
    //конструкторы
        //из массива созд список
        ListSequence(T* arr, int count) : items(arr, count) {}
        //пустая последовательность
        ListSequence() : items() {}
        //копирование из  линк лист в лист сик
        ListSequence(const LinkedList<T>& list) : items(list) {}
        //копирующий(лист сик в лист сик)
        ListSequence(const ListSequence<T>& other) : items(other.items) {}
};