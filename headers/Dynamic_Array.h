#pragma once
#include "Exception.h"
#include "Option.h"

template <typename T>
class Dynamic_Array {
    private:
        T* data; //* на дин массив el
        int size; //now size el
        int capacity; //емкость
        //выделение нового массива,copy data, del old
        void reallocate(int new_capacity) {
            T* new_data = new T[new_capacity]; //выделение нового массива в дин памяти
            int copy_count = (size < new_capacity) ? size : new_capacity;
            for (int i = 0; i < copy_count; ++i) {
                new_data[i] = data[i];
            }
            delete[] data;
            data = new_data;
            capacity = new_capacity;
            size = copy_count;
        }
    public:
        //создает массив-копию из существующего
        Dynamic_Array(T* items, int count) : size(count), capacity(count) {
            if (count < 0) throw InvalidArgumentException();
            data = new T[capacity];
            for (int i=0; i<size; ++i) {
                data[i] = items[i];
            }
        }
        //создает массив заданного размера (заполненый значениями по умолчанию)
        Dynamic_Array(int size = 0) : size(size), capacity(size > 0 ? size : 1) {
            if (size < 0) throw InvalidArgumentException();
            data = new T[capacity];
        }
        //копирует
        Dynamic_Array(const Dynamic_Array<T>& other) : size(other.size), capacity(other.capacity) {
            data = new T[capacity];
            for (int i=0; i<size; ++i) {
                data[i] = other.data[i];
            }
        }
        //деструктор
        ~Dynamic_Array() {
            delete[] data;
        }
        //присваивает один массив другому
        Dynamic_Array<T>& operator=(const Dynamic_Array<T>& other) {
            if (this != &other) {
                delete[] data;
                size = other.size;
                capacity = other.capacity;
                data = new T[capacity];
                for (int i=0; i<size; ++i) {
                    data[i] = other.data[i];
                }
            }
            return *this;
        }
        //доступ к эл массива по инд(неконстантному)
        T& operator[](int index) {
            if (index < 0 || index >= size) throw IndexOutOfRangeException();
            return data[index];
        }
        //доступ к эд массива по инд(константному)
        const T& operator[](int index) const {
            if (index < 0 || index >= size) throw IndexOutOfRangeException();
            return data[index];
        }
        //обертки над operator[]
        T& Get(int index) { return (*this)[index];}
        const T& Get(int index) const {return (*this)[index];}
        // Try-семантика: возвращает Option<T> вместо исключения
        Option<T> TryGet(int index) const {
                if (index < 0 || index >= size) {
                    return Option<T>();
                }
                return Option<T>((*this)[index]);
            }
        //присваивает эл с инд значение
        void Set(int index, const T& value) {(*this)[index] = value;}
        //возвращает текущий размер массива
        int GetSize() const {return size;}
        //изменение размера
        void Resize(int new_size) {
            if (new_size < 0) throw InvalidArgumentException();
            if (new_size > capacity) {
                int new_capacity = new_size * 2;
                reallocate(new_capacity);
                for (int i= size; i < new_size; ++i) {
                    data[i] = T();
                }
                size = new_size;
            }
            else if (new_size < size) {
                size = new_size; //не чистим тк прсто забываем, теперь это мусор в слотах капасити
            }
            else if (new_size > size) {
                for (int i=size; i<new_size; ++i) {
                    data[i] = T();
                }
                size = new_size;
            }
        }
        //удаление эл по индексу
        void RemoveAt(int index) {
            if (index < 0 || index >= size) {
                throw IndexOutOfRangeException();
            }
            //сдвигаем эл влево
            for (int i = index; i < size - 1; ++i) {
                data[i] = data[i+1];
            }
            --size;
        }
        //возвращает текущую емкость
        int GetCapacity() const {return capacity;}
        //итераторы
        typedef T* Iterator;
        typedef const T* ConstIterator;
        //пройтись по массиву не зная его устройства
        Iterator Begin() {return data;}
        ConstIterator Begin() const {return data;}
        Iterator End() {return data + size;}
        ConstIterator End() const {return data + size;}
};
