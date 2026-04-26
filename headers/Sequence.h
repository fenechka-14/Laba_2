#pragma once
#include "Option.h"

template <typename T>
class Sequence {
    public:
        //виртуальный деструктор
        virtual ~Sequence() {}
        //доступ к элементам (возвращает ссылку на эл по index)
        virtual T& Get(int index) = 0;
        //константная версия
        virtual const T& Get(int index) const = 0;
        //возвращает длину последовательности
        virtual int GetLength() const = 0;
        //первый эл (обычная и конст версия)
        virtual  T& GetFirst() = 0;
        virtual const T& GetFirst() const = 0;
        //тоже самое для последнего
        virtual  T& GetLast() = 0;
        virtual const T& GetLast() const = 0;
        //Try-семантика
        virtual  Option<T> TryGet(int index) const = 0; //безопасное получение эл
        virtual Option<T> TryGetFirst() const = 0; //безопасное получение 1го эл
        virtual Option<T> TryGetLast() const = 0; //безопасное получение последнего эл
    //операции (озвращает указатель на последовательности) для m - this, для im - clone
        virtual Sequence<T>* Append(const T& item) = 0; //добавление в конец
        virtual Sequence<T>* Prepend(const T& item) = 0; //добавление в конец
        virtual Sequence<T>* InsertAt(const T& item, int index) = 0; //вставка по индексу
        virtual void RemoveAt(int index) = 0; //удаление эл
        virtual Sequence<T>* Concat(Sequence<T>* other) = 0; //сцепление двух последовательностей
        virtual Sequence<T>* GetSubSequence(int startIndex, int endIndex) = 0; //получение последовательности
    //важный метод для mutable/immutable
        virtual Sequence<T>* Instance() = 0; //все методы юудут вызывать перед изменением
        virtual Sequence<T>* Clone() const = 0; //глубокая копия посл-сти
    // Map-Where-Reduce
        //(применяет функцию func к каждому эл)
        virtual Sequence<T>* Map(T (*func)(const T&)) {
            Sequence<T>* result = Instance(); //рабочий объект
            //заменяем каждый эл результатом func
            for (int i = 0; i < result->GetLength(); ++i) {
                result->Get(i) = func(result->Get(i));
            }
            return result;
        }
        //фильтрует элементы по условию pred
        virtual Sequence<T>* Where(bool (*pred)(const T&)) {
            Sequence<T>* result = Instance();
            for (int i = result->GetLength() - 1; i>=0; --i) {
                if (!pred(result->Get(i))) {
                    result->RemoveAt(i);
                }
            }
            return result;
        }
        //сворачивает посл-сть в одно значение
        virtual T Reduce(T (*func)(const T&, const T&), const T& init) const {
            T acc = init;
            for (int i = 0; i < GetLength(); ++i) {
                acc = func(acc, Get(i));
            }
            return acc;
        }
};