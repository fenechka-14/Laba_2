#include "../headers/BitSequence.h"
#include <iostream>

#define CHECK(condition, message) \
    if (!(condition)) { \
        std::cout << "[FAIL] " << message << std::endl; \
        return 1; \
    }

#define TEST_OK(name) \
    std::cout << "[OK] " << name << std::endl;

int main_BitSequence() {
    // ----------------------------------------------------------------------
    // Тест 1: Конструктор по размеру
    // ----------------------------------------------------------------------
    {
        BitSequence bits(5);
        CHECK(bits.GetLength() == 5, "Size constructor: length should be 5");
        CHECK(bits[0] == false, "Size constructor: all bits should be false");
        TEST_OK("Constructor with size");
    }

    // ----------------------------------------------------------------------
    // Тест 2: Конструктор из массива
    // ----------------------------------------------------------------------
    {
        bool arr[] = {true, false, true, false, true};
        BitSequence bits(arr, 5);
        CHECK(bits.GetLength() == 5, "Array constructor: length should be 5");
        CHECK(bits[0] == true, "Array constructor: bits[0] should be true");
        CHECK(bits[1] == false, "Array constructor: bits[1] should be false");
        CHECK(bits[2] == true, "Array constructor: bits[2] should be true");
        CHECK(bits[4] == true, "Array constructor: bits[4] should be true");
        TEST_OK("Constructor from array");
    }

    // ----------------------------------------------------------------------
    // Тест 3: Get и Set
    // ----------------------------------------------------------------------
    {
        BitSequence bits(4);
        bits.Set(0, true);
        CHECK(bits.Get(0) == true, "Set: bit 0 should be true");
        bits.Set(1, false);
        CHECK(bits.Get(1) == false, "Set: bit 1 should be false");
        bits.Set(0, false);
        CHECK(bits.Get(0) == false, "Set: bit 0 should be false after second set");
        TEST_OK("Get and Set");
    }

    // ----------------------------------------------------------------------
    // Тест 4: operator[]
    // ----------------------------------------------------------------------
    {
        bool arr[] = {false, true, false};
        BitSequence bits(arr, 3);
        CHECK(bits[0] == false, "operator[]: bits[0] should be false");
        CHECK(bits[1] == true, "operator[]: bits[1] should be true");
        CHECK(bits[2] == false, "operator[]: bits[2] should be false");
        TEST_OK("operator[]");
    }

    // ----------------------------------------------------------------------
    // Тест 5: Копирующий конструктор
    // ----------------------------------------------------------------------
    {
        bool arr[] = {true, false, true};
        BitSequence bits1(arr, 3);
        BitSequence bits2(bits1);
        CHECK(bits2.GetLength() == 3, "Copy constructor: length should be 3");
        CHECK(bits2[0] == true, "Copy constructor: bits2[0] should be true");
        bits1.Set(0, false);
        CHECK(bits2[0] == true, "Copy constructor: deep copy - bits2[0] should remain true");
        TEST_OK("Copy constructor");
    }

    // ----------------------------------------------------------------------
    // Тест 6: Оператор присваивания
    // ----------------------------------------------------------------------
    {
        bool arr[] = {false, true};
        BitSequence bits1(arr, 2);
        BitSequence bits2;
        bits2 = bits1;
        CHECK(bits2.GetLength() == 2, "Assignment: length should be 2");
        CHECK(bits2[0] == false, "Assignment: bits2[0] should be false");
        CHECK(bits2[1] == true, "Assignment: bits2[1] should be true");
        bits2 = bits2;
        CHECK(bits2.GetLength() == 2, "Assignment: self-assign length should stay 2");
        TEST_OK("Assignment operator");
    }

    // ----------------------------------------------------------------------
    // Тест 7: CountOnes
    // ----------------------------------------------------------------------
    {
        bool arr[] = {true, false, true, true, false};
        BitSequence bits(arr, 5);
        CHECK(bits.CountOnes() == 3, "CountOnes: should be 3");
        TEST_OK("CountOnes");
    }

    // ----------------------------------------------------------------------
    // Тест 8: CountZeros
    // ----------------------------------------------------------------------
    {
        bool arr[] = {true, false, true, false};
        BitSequence bits(arr, 4);
        CHECK(bits.CountZeros() == 2, "CountZeros: should be 2");
        TEST_OK("CountZeros");
    }

    // ----------------------------------------------------------------------
    // Тест 9: SetAll
    // ----------------------------------------------------------------------
    {
        BitSequence bits(4);
        bits.SetAll();
        CHECK(bits[0] == true, "SetAll: bit 0 should be true");
        CHECK(bits[1] == true, "SetAll: bit 1 should be true");
        CHECK(bits[3] == true, "SetAll: bit 3 should be true");
        CHECK(bits.CountOnes() == 4, "SetAll: all 4 bits should be 1");
        TEST_OK("SetAll");
    }

    // ----------------------------------------------------------------------
    // Тест 10: ResetAll
    // ----------------------------------------------------------------------
    {
        bool arr[] = {true, true, true};
        BitSequence bits(arr, 3);
        bits.ResetAll();
        CHECK(bits[0] == false, "ResetAll: bit 0 should be false");
        CHECK(bits[1] == false, "ResetAll: bit 1 should be false");
        CHECK(bits.CountOnes() == 0, "ResetAll: all bits should be 0");
        TEST_OK("ResetAll");
    }

    // ----------------------------------------------------------------------
    // Тест 11: InvertAll
    // ----------------------------------------------------------------------
    {
        bool arr[] = {true, false, true, false};
        BitSequence bits(arr, 4);
        bits.InvertAll();
        CHECK(bits[0] == false, "InvertAll: bit 0 should be false");
        CHECK(bits[1] == true, "InvertAll: bit 1 should be true");
        CHECK(bits[2] == false, "InvertAll: bit 2 should be false");
        CHECK(bits[3] == true, "InvertAll: bit 3 should be true");
        TEST_OK("InvertAll");
    }

    // ----------------------------------------------------------------------
    // Тест 12: Исключение IndexOutOfRangeException
    // ----------------------------------------------------------------------
    {
        BitSequence bits(4);
        bool caught = false;
        try { bits.Get(5); }
        catch (const IndexOutOfRangeException&) { caught = true; }
        CHECK(caught, "IndexOutOfRange: should throw on index >= length");

        caught = false;
        try { bits.Set(-1, true); }
        catch (const IndexOutOfRangeException&) { caught = true; }
        CHECK(caught, "IndexOutOfRange: should throw on negative index");
        TEST_OK("IndexOutOfRangeException");
    }

    // ----------------------------------------------------------------------
    // Тест 13: Исключение InvalidArgumentException
    // ----------------------------------------------------------------------
    {
        bool caught = false;
        try { BitSequence bits(-5); }
        catch (const InvalidArgumentException&) { caught = true; }
        CHECK(caught, "InvalidArgument: negative size");

        caught = false;
        try { BitSequence bits(33); }
        catch (const InvalidArgumentException&) { caught = true; }
        CHECK(caught, "InvalidArgument: size > 32");
        TEST_OK("InvalidArgumentException");
    }

    std::cout << std::endl << "=== BitSequence TESTS PASSED ===" << std::endl;
    return 0;
}