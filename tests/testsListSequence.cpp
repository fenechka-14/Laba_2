#include "../headers/MutableListSequence.h"
#include "../headers/ImmutableListSequence.h"
#include <iostream>

#define CHECK(condition, message) \
    if (!(condition)) { \
        std::cout << "[FAIL] " << message << std::endl; \
        return 1; \
    }

#define TEST_OK(name) \
    std::cout << "[OK] " << name << std::endl;

int main_ListSequence() {
    // ----------------------------------------------------------------------
    // Тест 1: Конструктор по умолчанию
    // ----------------------------------------------------------------------
    {
        MutableListSequence<int> seq;
        CHECK(seq.GetLength() == 0, "Default constructor: length should be 0");
        TEST_OK("Constructor default (empty list sequence)");
    }

    // ----------------------------------------------------------------------
    // Тест 2: Конструктор из массива
    // ----------------------------------------------------------------------
    {
        int arr[] = {10, 20, 30, 40, 50};
        MutableListSequence<int> seq(arr, 5);
        CHECK(seq.GetLength() == 5, "Array constructor: length should be 5");
        CHECK(seq.Get(0) == 10, "Array constructor: seq[0] should be 10");
        CHECK(seq.Get(2) == 30, "Array constructor: seq[2] should be 30");
        CHECK(seq.Get(4) == 50, "Array constructor: seq[4] should be 50");
        TEST_OK("Constructor from array");
    }

    // ----------------------------------------------------------------------
    // Тест 3: Копирующий конструктор
    // ----------------------------------------------------------------------
    {
        int arr[] = {1, 2, 3};
        MutableListSequence<int> seq1(arr, 3);
        MutableListSequence<int> seq2(seq1);

        CHECK(seq2.GetLength() == 3, "Copy constructor: length should be 3");
        CHECK(seq2.Get(0) == 1, "Copy constructor: seq2[0] should be 1");
        CHECK(seq2.Get(1) == 2, "Copy constructor: seq2[1] should be 2");
        CHECK(seq2.Get(2) == 3, "Copy constructor: seq2[2] should be 3");

        seq1.Get(0) = 99;
        CHECK(seq2.Get(0) == 1, "Copy constructor: deep copy");
        TEST_OK("Copy constructor (deep copy)");
    }

    // ----------------------------------------------------------------------
    // Тест 4: GetFirst и GetLast
    // ----------------------------------------------------------------------
    {
        int arr[] = {10, 20, 30};
        MutableListSequence<int> seq(arr, 3);
        CHECK(seq.GetFirst() == 10, "GetFirst: should be 10");
        CHECK(seq.GetLast() == 30, "GetLast: should be 30");
        seq.GetFirst() = 99;
        CHECK(seq.GetFirst() == 99, "GetFirst write: should be 99");
        seq.GetLast() = 77;
        CHECK(seq.GetLast() == 77, "GetLast write: should be 77");
        TEST_OK("GetFirst and GetLast");
    }

    // ----------------------------------------------------------------------
    // Тест 5: Append
    // ----------------------------------------------------------------------
    {
        MutableListSequence<int> seq;
        seq.Append(10);
        CHECK(seq.GetLength() == 1, "Append: length should be 1");
        CHECK(seq.Get(0) == 10, "Append: seq[0] should be 10");
        seq.Append(20);
        CHECK(seq.GetLength() == 2, "Append: length should be 2");
        CHECK(seq.Get(1) == 20, "Append: seq[1] should be 20");
        TEST_OK("Append");
    }

    // ----------------------------------------------------------------------
    // Тест 6: Prepend
    // ----------------------------------------------------------------------
    {
        MutableListSequence<int> seq;
        seq.Prepend(30);
        CHECK(seq.Get(0) == 30, "Prepend: seq[0] should be 30");
        seq.Prepend(20);
        CHECK(seq.Get(0) == 20, "Prepend: seq[0] should be 20");
        CHECK(seq.Get(1) == 30, "Prepend: seq[1] should be 30");
        TEST_OK("Prepend");
    }

    // ----------------------------------------------------------------------
    // Тест 7: InsertAt
    // ----------------------------------------------------------------------
    {
        int arr[] = {10, 30, 40};
        MutableListSequence<int> seq(arr, 3);
        seq.InsertAt(20, 1);
        CHECK(seq.Get(0) == 10, "InsertAt: seq[0] should be 10");
        CHECK(seq.Get(1) == 20, "InsertAt: seq[1] should be 20");
        CHECK(seq.Get(2) == 30, "InsertAt: seq[2] should be 30");
        CHECK(seq.Get(3) == 40, "InsertAt: seq[3] should be 40");
        TEST_OK("InsertAt");
    }

    // ----------------------------------------------------------------------
    // Тест 8: RemoveAt
    // ----------------------------------------------------------------------
    {
        int arr[] = {10, 20, 30, 40, 50};
        MutableListSequence<int> seq(arr, 5);
        seq.RemoveAt(2);
        CHECK(seq.GetLength() == 4, "RemoveAt: length should be 4");
        CHECK(seq.Get(0) == 10, "RemoveAt: seq[0] should be 10");
        CHECK(seq.Get(1) == 20, "RemoveAt: seq[1] should be 20");
        CHECK(seq.Get(2) == 40, "RemoveAt: seq[2] should be 40");
        CHECK(seq.Get(3) == 50, "RemoveAt: seq[3] should be 50");
        TEST_OK("RemoveAt");
    }

    // ----------------------------------------------------------------------
    // Тест 9: Concat
    // ----------------------------------------------------------------------
    {
        int arr1[] = {1, 2};
        int arr2[] = {3, 4};
        MutableListSequence<int> seq1(arr1, 2);
        MutableListSequence<int> seq2(arr2, 2);
        Sequence<int>* result = seq1.Concat(&seq2);
        CHECK(result->GetLength() == 4, "Concat: length should be 4");
        CHECK(result->Get(0) == 1, "Concat: result[0] should be 1");
        CHECK(result->Get(3) == 4, "Concat: result[3] should be 4");
        TEST_OK("Concat");
    }

    // ----------------------------------------------------------------------
    // Тест 10: GetSubSequence
    // ----------------------------------------------------------------------
    {
        int arr[] = {10, 20, 30, 40, 50};
        MutableListSequence<int> seq(arr, 5);
        Sequence<int>* sub = seq.GetSubSequence(1, 3);
        CHECK(sub->GetLength() == 3, "GetSubSequence: length should be 3");
        CHECK(sub->Get(0) == 20, "GetSubSequence: sub[0] should be 20");
        CHECK(sub->Get(1) == 30, "GetSubSequence: sub[1] should be 30");
        CHECK(sub->Get(2) == 40, "GetSubSequence: sub[2] should be 40");
        CHECK(seq.GetLength() == 5, "GetSubSequence: original should not change");
        delete sub;
        TEST_OK("GetSubSequence");
    }

    // ----------------------------------------------------------------------
    // Тест 11: TryGet
    // ----------------------------------------------------------------------
    {
        int arr[] = {10, 20, 30};
        MutableListSequence<int> seq(arr, 3);
        Option<int> result = seq.TryGet(1);
        CHECK(result.IsSome() == true, "TryGet success: IsSome should be true");
        CHECK(result.Get() == 20, "TryGet success: Get should return 20");

        Option<int> fail = seq.TryGet(5);
        CHECK(fail.IsNone() == true, "TryGet fail: IsNone should be true");
        CHECK(fail.GetOrElse(-1) == -1, "TryGet fail: GetOrElse should return default");
        TEST_OK("TryGet");
    }

    // ----------------------------------------------------------------------
    // Тест 12: TryGetFirst / TryGetLast
    // ----------------------------------------------------------------------
    {
        int arr[] = {10, 20, 30};
        MutableListSequence<int> seq(arr, 3);
        CHECK(seq.TryGetFirst().Get() == 10, "TryGetFirst: should be 10");
        CHECK(seq.TryGetLast().Get() == 30, "TryGetLast: should be 30");
        TEST_OK("TryGetFirst and TryGetLast");
    }

    // ----------------------------------------------------------------------
    // Тест 13: Mutable — меняет оригинал
    // ----------------------------------------------------------------------
    {
        int arr[] = {1, 2, 3};
        MutableListSequence<int> seq(arr, 3);
        seq.Append(4);
        CHECK(seq.GetLength() == 4, "Mutable Append: length should be 4");
        CHECK(seq.Get(3) == 4, "Mutable Append: seq[3] should be 4");
        TEST_OK("Mutable changes original");
    }

    // ----------------------------------------------------------------------
    // Тест 14: Immutable — не меняет оригинал
    // ----------------------------------------------------------------------
    {
        int arr[] = {1, 2, 3};
        ImmutableListSequence<int> seq(arr, 3);
        Sequence<int>* newSeq = seq.Append(4);
        CHECK(seq.GetLength() == 3, "Immutable: original length should stay 3");
        CHECK(newSeq->GetLength() == 4, "Immutable: new length should be 4");
        CHECK(newSeq->Get(3) == 4, "Immutable: new[3] should be 4");
        CHECK(seq.Get(2) == 3, "Immutable: original[2] should stay 3");
        delete newSeq;
        TEST_OK("Immutable does not change original");
    }

    // ----------------------------------------------------------------------
    // Тест 15: Immutable Prepend
    // ----------------------------------------------------------------------
    {
        int arr[] = {2, 3};
        ImmutableListSequence<int> seq(arr, 2);
        Sequence<int>* newSeq = seq.Prepend(1);
        CHECK(seq.Get(0) == 2, "Immutable Prepend: original[0] should stay 2");
        CHECK(newSeq->Get(0) == 1, "Immutable Prepend: new[0] should be 1");
        delete newSeq;
        TEST_OK("Immutable Prepend");
    }

    std::cout << std::endl << "=== ListSequence TESTS PASSED ===" << std::endl;
    return 0;
}