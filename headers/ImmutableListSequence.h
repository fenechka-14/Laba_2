#pragma once

#include "ListSequence.h"

template <typename T>
class ImmutableListSequence : public ListSequence<T> {
public:
    using ListSequence<T>::ListSequence;

    Sequence<T>* Instance() override { return this->Clone(); }   // меняем копию
    Sequence<T>* Clone() const override { return new ImmutableListSequence<T>(this->items); }
};