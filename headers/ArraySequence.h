#pragma once

#include "Sequence.h"
#include "DynamicArray.h"

template <typename T>
class ArraySequence : public Sequence<T> {
    protected:
        DynamicArray<T> items;
    public:
    //конструкторы
        //копия существующего массива(обычного дин) через *
        ArraySequence(T* arr, int count) : items(arr, count) {}
        //пустой массив
        ArraySequence() : items() {}
        //копия существующего дин массива(класс) через &
        ArraySequence(const DynamicArray<T>& arr) : items(arr) {}
        //копирует
        ArraySequence(const ArraySequence<T>& other) : items(other.items) {}
    //доступ к элементам
        //получение элемента по index
        T& Get(int index) override { return items[index]; }
        const T& Get(int index) const override { return items[index]; }
        //длина последовательности
        int GetLength() const override { return items.GetSize(); }
        //первый элемент
        T& GetFirst() override { return items[0]; }
        const T& GetFirst() const override { return items[0]; }
        //последний элемент
        T& GetLast() override { return items[items.GetSize()-1]; }
        const T& GetLast() const override { return items[items.GetSize()-1]; }
    //Try-семантика
        //Some(value) если index в границах, None если нет
        Option<T> TryGet(int index) const override {
            return items.TryGet(index);
        }
        //если массив пуст - none, иначе some(первый эл)
        Option<T> TryGetFirst() const override {
            if (items.GetSize() == 0) return Option<T>();
            return Option<T>(items[0]);
        }
        //тоже самое для последнего
        Option<T> TryGetLast() const override {
            if (items.GetSize() == 0) return Option<T>();
            return Option<T>(items[items.GetSize()-1]);
        }
    //операции
        //Append
        Sequence<T>* Append(const T& item) override {
            Sequence<T>* inst = Instance();
            ArraySequence<T>* self = dynamic_cast<ArraySequence<T>*>(inst);
            self->items.Resize(self->items.GetSize() + 1);
            self->items[self->items.GetSize() - 1] = item;
            return inst;
        }
        //Prepend
        Sequence<T>* Prepend(const T& item) override {
            Sequence<T>* inst = Instance();
            ArraySequence<T>* self = dynamic_cast<ArraySequence<T>*>(inst);
            int oldSize = self->items.GetSize();
            self->items.Resize(oldSize + 1);
            for (int i = oldSize; i > 0; --i) {
                self->items[i] = self->items[i - 1];
            }
            self->items[0] = item;
            return inst;
        }
        //InsertAt (вставка по ind)
        Sequence<T>* InsertAt(const T& item, int index) override {
            Sequence<T>* inst = Instance();
            ArraySequence<T>* self = dynamic_cast<ArraySequence<T>*>(inst);
            if (index < 0 || index > self->items.GetSize()) {
                throw IndexOutOfRangeException();
            }
            int oldSize = self->items.GetSize();
            self->items.Resize(oldSize + 1);
            for (int i = oldSize; i > index; --i) {
                self->items[i] = self->items[i - 1];
            }
            self->items[index] = item;
            return inst;
        }
        //RemoveAt (удаление по index)
        void RemoveAt(int index) override {
            Sequence<T>* inst = Instance();
            ArraySequence<T>* self = dynamic_cast<ArraySequence<T>*>(inst);
            self->items.RemoveAt(index);
        }
        //Concat
        Sequence<T>* Concat(Sequence<T>* other) override {
            Sequence<T>* inst = Instance();
            ArraySequence<T>* self = dynamic_cast<ArraySequence<T>*>(inst);
            int oldSize = self->items.GetSize();
            int otherLen = other->GetLength();
            self->items.Resize(oldSize + otherLen);
            for (int i = 0; i < otherLen; ++i) {
                self->items[oldSize + i] = other->Get(i);
            }
            return inst;
        }
        //GetSubsequence (подпоследовательность)
        Sequence<T>* GetSubSequence(int startIndex, int endIndex) override {
            if (startIndex < 0 || endIndex >= items.GetSize() || startIndex > endIndex) {
                throw IndexOutOfRangeException();
            }
            int newSize = endIndex - startIndex + 1;
            Sequence<T>* result = this->Clone(); //всегда копия (тк операция чтения)
            result->Resize(newSize);
            for (int i = 0; i < newSize; ++i) {
                result->Get(i) = items[startIndex + i];
            }
            return result;
        }
        //Resize
        void Resize(int newSize) override {
                items.Resize(newSize);
            }
    // чисто виртуальные методы
        virtual Sequence<T>* Instance() override = 0;
        virtual  Sequence<T>* Clone() const override = 0;
};
