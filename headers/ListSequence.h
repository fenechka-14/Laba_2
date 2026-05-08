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
    // доступ к элементам
        //получение элемента по index
        T& Get(int index) override {return items[index]; }
        const T& Get(int index) const override {return items[index]; }
        //длина последовательности
        int GetLength() const override { return items.GetLength(); }
        //первый эл
        T& GetFirst() override { return items.GetFirst(); }
        const T& GetFirst() const override { return items.GetFirst(); }
        //последний эл
        T& GetLast() override { return items.GetLast(); }
        const T& GetLast() const override { return items.GetLast(); }
    //Try-семантика
        //безопасное получение эл
        Option<T> TryGet(int index) const override { return items.TryGet(index); }
        //если список пуст - none, иначе some(первый эл)
        Option<T> TryGetFirst() const override {
            if (items.GetLength() == 0) return Option<T>();
            return Option<T>(items.GetFirst());
        }
        //аналогично для последнего
        Option<T> TryGetLast() const override {
            if (items.GetLength() == 0) return Option<T>();
            return Option<T>(items.GetLast());
        }
    //операции
        //Append
        Sequence<T>* Append(const T& item) override {
            Sequence<T>* inst = Instance();
            ListSequence<T>* self = dynamic_cast<ListSequence<T>*>(inst);
            self->items.Append(item);
            return inst;
        }
        //Prepend
        Sequence<T>* Prepend(const T& item) override {
            Sequence<T>* inst = Instance();
            ListSequence<T>* self = dynamic_cast<ListSequence<T>*>(inst);
            self->items.Prepend(item);
            return inst;
        }
        //InsertAt (вставка по индексу)
        Sequence<T>* InsertAt(const T& item, int index) override {
            Sequence<T>* inst = Instance();
            ListSequence<T>* self = dynamic_cast<ListSequence<T>*>(inst);
            self->items.InsertAt(item, index);
            return inst;
        }
        //RemoveAt (удаление по индексу)
        void RemoveAt(int index) override {
            Sequence<T>* inst = Instance();
            ListSequence<T>* self = dynamic_cast<ListSequence<T>*>(inst);
            self->items.RemoveAt(index);
        }
        //Concat
        Sequence<T>* Concat(Sequence<T>* other) override {
            Sequence<T>* inst = Instance();
            ListSequence<T>* self = dynamic_cast<ListSequence<T>*>(inst);
            for (int i = 0; i < other->GetLength(); ++i) {
                self->items.Append(other->Get(i));
            }
            return inst;
        }
        //подпоследовательность
        Sequence<T>* GetSubSequence(int startIndex, int endIndex) override {
            if (startIndex < 0 || endIndex >= items.GetLength() || startIndex > endIndex) {
                throw IndexOutOfRangeException();
            }
            int newSize = endIndex - startIndex + 1;
            Sequence<T>* result = this->Clone();
            result->Resize(newSize);
            for (int i = 0; i < newSize; ++i) {
                result->Get(i) = items[startIndex + i];
            }
            return result;
        }
        //Resize для подпоследовательности
        void Resize(int newSize) override {
            if (newSize > items.GetLength()) {
                int add = newSize - items.GetLength();
                for (int i = 0; i < add; ++i) items.Append(T());
            } else if (newSize < items.GetLength()) {
                int remove = items.GetLength() - newSize;
                for (int i = 0; i < remove; ++i) items.RemoveAt(items.GetLength() - 1);
            }
        }
    //чисто виртуальные методы
        virtual Sequence<T>* Instance() override = 0;
        virtual Sequence<T>* Clone() const override = 0;
};