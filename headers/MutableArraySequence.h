#pragma once

#include "ArraySequence.h"

template <typename T>
class MutableArraySequence : public ArraySequence<T> {
public:
    using ArraySequence<T>::ArraySequence;

    Sequence<T>* Instance() override { return this; }
    Sequence<T>* Clone() const override { return new MutableArraySequence<T>(this->items); }
};