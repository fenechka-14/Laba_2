#pragma once

#include "Exception.h"

class BitSequence {
    private:
        unsigned int data;
        int length;
    public:
    //конструкторы
        //по размеру
        BitSequence(int size = 0) : data(0), length(size) {
            if (size < 0 || size > 32) throw InvalidArgumentException();
        }
        //из массива
        BitSequence(const bool* items, int count) : data(0), length(count) {
            if (count < 0 || count > 32) throw InvalidArgumentException();
            for (int i = 0; i < count; ++i) {
                if (items[i]) data |= (1u << i);
            }
        }
        //копирующий
        BitSequence(const BitSequence& other) : data(other.data), length(other.length) {}
        //чтение бита по индексу
        bool Get(int index) const {
            if (index < 0 || index >= length) throw IndexOutOfRangeException();
            return (data >> index) & 1u;
        }
        //запись бита по индексу
        void Set(int index, bool value) {
            if (index < 0 || index >= length) throw IndexOutOfRangeException();
            if (value) data |= (1u << index);
            else data &= ~(1u << index);
        }
        //возвращает кол-во битов
        int GetLength() const { return length; }
        //operator
        bool operator[](int index) const { return Get(index); }
        //оператор присваивания
        BitSequence& operator=(const BitSequence& other) {
        if (this != &other) { data = other.data; length = other.length; }
            return *this;
        }
        //подсчет единиц
        int CountOnes() const {
            int count = 0;
            unsigned int temp = data;
            while (temp) {
                count += (temp & 1u);
                temp >>= 1;
            }
            return count;
        }
        //подсчет нулей
        int CountZeros() const { return length - CountOnes(); }
        //установить все биты в 1
        void SetAll() {
            data = (length == 32) ? 0xFFFFFFFF : (1u << length) - 1;
        }
        //сбросить все биты в 0
        void ResetAll() { data = 0; }
        //инвертировать все биты
        void InvertAll() {
            data = ~data;
            if (length < 32) data &= (1u << length) - 1;
        }
        BitSequence And(const BitSequence& other) const {
                if (length != other.length) throw InvalidArgumentException();
                BitSequence result(length);
                result.data = data & other.data;
                return result;
            }

        BitSequence Or(const BitSequence& other) const {
                if (length != other.length) throw InvalidArgumentException();
                BitSequence result(length);
                result.data = data | other.data;
                return result;
            }

        BitSequence Xor(const BitSequence& other) const {
                if (length != other.length) throw InvalidArgumentException();
                BitSequence result(length);
                result.data = data ^ other.data;
                return result;
            }

        BitSequence Not() const {
                BitSequence result(length);
                result.data = ~data;
                if (length < 32) result.data &= (1u << length) - 1;
                return result;
            }
};