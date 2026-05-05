#pragma once

class Exception {
public:
    virtual  ~Exception() {} //виртуальный деструктор
    virtual const char* what() const=0; //перехват ошибки
};

//далее переопределенные методы what() для каждой ошибки
class IndexOutOfRangeException : public Exception {
public:
    const char* what() const override {
        return "Index out of range";
    }
};

class InvalidArgumentException : public Exception {
public:
    const char* what() const override {
        return "Invalid argument";
    }
};

class EmptyStructerException : public Exception {
public:
    const char* what() const override {
        return "Empty structer";
    }
};
