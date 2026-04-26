#pragma once
#include "Exception.h"

template <typename T>
class Option {
    private:
        T value; //само значение если оно есть, мб none
        bool hasValue; //if есть t, иначе f
    public:
        Option() : hasValue(false) {} //конструктор по умолчанию (пустой)
        Option(const T& val) : value(val), hasValue(true) {} //конструктор со значением
        //проверка наличия значения
        bool IsSome() const {
            return hasValue;
        }
        //проверка отсутсвия значения
        bool IsNone() const {
            return !hasValue;
        }
        //получение значение
        T& Get() {
            if (!hasValue) throw EmptyStructerException();
            return value;
        }
        //получение значения конст
        const T& Get() const {
            if (!hasValue) throw EmptyStructerException();
            return value;
        }
        //получить значение или замену
        T GetOrElse(const T& defaultValue) const {
            return hasValue ? value : defaultValue;
        }
};