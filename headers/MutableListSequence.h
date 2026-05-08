#pragma once

#include "ListSequence.h"

template <typename T>
class MutableListSequence : public ListSequence<T> {
public:
    using ListSequence<T>::ListSequence;   // наследуем все конструкторы

    Sequence<T>* Instance() override { return this; }   // меняем оригинал
    Sequence<T>* Clone() const override { return new MutableListSequence<T>(this->items); }
};