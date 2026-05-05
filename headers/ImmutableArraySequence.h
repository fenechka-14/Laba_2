#pragma once

#include "ArraySequence.h"

template <typename T>
class ImmutableArraySequence : public ArraySequence<T> {
public:
    using ArraySequence<T>::ArraySequence;

    Sequence<T>* Instance() override { return this->Clone(); }
    Sequence<T>* Clone() const override { return new ImmutableArraySequence<T>(this->items); }
};