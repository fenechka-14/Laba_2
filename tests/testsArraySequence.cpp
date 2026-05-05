#include "../headers/MutableArraySequence.h"
#include "../headers/ImmutableArraySequence.h"
#include <iostream>

#define CHECK(condition, message) \
    if (!(condition)) { \
        std::cout << "[FAIL] " << message << std::endl; \
        return 1; \
    }

#define TEST_OK(name) \
    std::cout << "[OK] " << name << std::endl;

int main_ArraySequence() {
    // ----------------------------------------------------------------------
    // Тест 1: Конструктор по умолчанию
    // ----------------------------------------------------------------------
    {
        MutableArraySequence<int> seq;
        CHECK(seq.GetLength() == 0, "Default constructor: length should be 0");
        TEST_OK("Constructor default (empty sequence)");
    }

    // ----------------------------------------------------------------------
    // Тест 2: Конструктор из массива
    // ----------------------------------------------------------------------
    {
        int arr[] = {10, 20, 30, 40, 50};
        MutableArraySequence<int> seq(arr, 5);
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
        MutableArraySequence<int> seq1(arr, 3);
        MutableArraySequence<int> seq2(seq1);

        CHECK(seq2.GetLength() == 3, "Copy constructor: length should be 3");
        CHECK(seq2.Get(0) == 1, "Copy constructor: seq2[0] should be 1");
        CHECK(seq2.Get(1) == 2, "Copy constructor: seq2[1] should be 2");
        CHECK(seq2.Get(2) == 3, "Copy constructor: seq2[2] should be 3");

        seq1.Get(0) = 99;
        CHECK(seq2.Get(0) == 1, "Copy constructor: deep copy - seq2[0] should remain 1");
        TEST_OK("Copy constructor (deep copy)");
    }

    // ----------------------------------------------------------------------
    // Тест 4: GetFirst и GetLast
    // ----------------------------------------------------------------------
    {
        int arr[] = {10, 20, 30};
        MutableArraySequence<int> seq(arr, 3);

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
        MutableArraySequence<int> seq;
        seq.Append(10);
        CHECK(seq.GetLength() == 1, "Append: length should be 1");
        CHECK(seq.Get(0) == 10, "Append: seq[0] should be 10");

        seq.Append(20);
        CHECK(seq.GetLength() == 2, "Append: length should be 2");
        CHECK(seq.Get(1) == 20, "Append: seq[1] should be 20");

        seq.Append(30);
        CHECK(seq.GetLength() == 3, "Append: length should be 3");
        CHECK(seq.Get(0) == 10, "Append: order - seq[0] should be 10");
        CHECK(seq.Get(1) == 20, "Append: order - seq[1] should be 20");
        CHECK(seq.Get(2) == 30, "Append: order - seq[2] should be 30");
        TEST_OK("Append");
    }

    // ----------------------------------------------------------------------
    // Тест 6: Prepend
    // ----------------------------------------------------------------------
    {
        MutableArraySequence<int> seq;
        seq.Prepend(30);
        CHECK(seq.GetLength() == 1, "Prepend: length should be 1");
        CHECK(seq.Get(0) == 30, "Prepend: seq[0] should be 30");

        seq.Prepend(20);
        CHECK(seq.GetLength() == 2, "Prepend: length should be 2");
        CHECK(seq.Get(0) == 20, "Prepend: seq[0] should be 20");
        CHECK(seq.Get(1) == 30, "Prepend: seq[1] should be 30");

        seq.Prepend(10);
        CHECK(seq.GetLength() == 3, "Prepend: length should be 3");
        CHECK(seq.Get(0) == 10, "Prepend: seq[0] should be 10");
        CHECK(seq.Get(1) == 20, "Prepend: seq[1] should be 20");
        CHECK(seq.Get(2) == 30, "Prepend: seq[2] should be 30");
        TEST_OK("Prepend");
    }

    // ----------------------------------------------------------------------
    // Тест 7: InsertAt
    // ----------------------------------------------------------------------
    {
        int arr[] = {10, 30, 40};
        MutableArraySequence<int> seq(arr, 3);

        seq.InsertAt(20, 1);
        CHECK(seq.GetLength() == 4, "InsertAt middle: length should be 4");
        CHECK(seq.Get(0) == 10, "InsertAt middle: seq[0] should be 10");
        CHECK(seq.Get(1) == 20, "InsertAt middle: seq[1] should be 20");
        CHECK(seq.Get(2) == 30, "InsertAt middle: seq[2] should be 30");
        CHECK(seq.Get(3) == 40, "InsertAt middle: seq[3] should be 40");

        seq.InsertAt(5, 0);
        CHECK(seq.GetLength() == 5, "InsertAt beginning: length should be 5");
        CHECK(seq.Get(0) == 5, "InsertAt beginning: seq[0] should be 5");

        seq.InsertAt(50, seq.GetLength());
        CHECK(seq.GetLength() == 6, "InsertAt end: length should be 6");
        CHECK(seq.Get(5) == 50, "InsertAt end: seq[5] should be 50");
        TEST_OK("InsertAt");
    }

    // ----------------------------------------------------------------------
    // Тест 8: RemoveAt
    // ----------------------------------------------------------------------
    {
        int arr[] = {10, 20, 30, 40, 50};
        MutableArraySequence<int> seq(arr, 5);

        // Удаляем середину (30)
        seq.RemoveAt(2);
        CHECK(seq.GetLength() == 4, "RemoveAt middle: length should be 4");
        CHECK(seq.Get(0) == 10, "RemoveAt middle: seq[0] should be 10");
        CHECK(seq.Get(1) == 20, "RemoveAt middle: seq[1] should be 20");
        CHECK(seq.Get(2) == 40, "RemoveAt middle: seq[2] should be 40");
        CHECK(seq.Get(3) == 50, "RemoveAt middle: seq[3] should be 50");

        // Удаляем начало (20)
        seq.RemoveAt(0);
        CHECK(seq.GetLength() == 3, "RemoveAt first: length should be 3");
        CHECK(seq.Get(0) == 20, "RemoveAt first: seq[0] should be 20");
        CHECK(seq.Get(1) == 40, "RemoveAt first: seq[1] should be 40");
        CHECK(seq.Get(2) == 50, "RemoveAt first: seq[2] should be 50");

        // Удаляем конец (50)
        seq.RemoveAt(seq.GetLength() - 1);
        CHECK(seq.GetLength() == 2, "RemoveAt last: length should be 2");
        CHECK(seq.Get(0) == 20, "RemoveAt last: seq[0] should be 20");
        CHECK(seq.Get(1) == 40, "RemoveAt last: seq[1] should be 40");

        TEST_OK("RemoveAt");
    }
    // ----------------------------------------------------------------------
    // Тест 9: Concat
    // ----------------------------------------------------------------------
    {
        int arr1[] = {1, 2, 3};
        int arr2[] = {4, 5};
        MutableArraySequence<int> seq1(arr1, 3);
        MutableArraySequence<int> seq2(arr2, 2);

        Sequence<int>* result = seq1.Concat(&seq2);
        CHECK(result->GetLength() == 5, "Concat: length should be 5");
        CHECK(result->Get(0) == 1, "Concat: result[0] should be 1");
        CHECK(result->Get(1) == 2, "Concat: result[1] should be 2");
        CHECK(result->Get(2) == 3, "Concat: result[2] should be 3");
        CHECK(result->Get(3) == 4, "Concat: result[3] should be 4");
        CHECK(result->Get(4) == 5, "Concat: result[4] should be 5");
        TEST_OK("Concat");
    }

    // ----------------------------------------------------------------------
    // Тест 10: GetSubsequence
    // ----------------------------------------------------------------------
    {
        int arr[] = {10, 20, 30, 40, 50};
        MutableArraySequence<int> seq(arr, 5);

        Sequence<int>* sub = seq.GetSubSequence(1, 3);
        CHECK(sub->GetLength() == 3, "GetSubsequence: length should be 3");
        CHECK(sub->Get(0) == 20, "GetSubsequence: sub[0] should be 20");
        CHECK(sub->Get(1) == 30, "GetSubsequence: sub[1] should be 30");
        CHECK(sub->Get(2) == 40, "GetSubsequence: sub[2] should be 40");
        delete sub;
        TEST_OK("GetSubsequence");
    }

    // ----------------------------------------------------------------------
    // Тест 11: TryGet (успех)
    // ----------------------------------------------------------------------
    {
        int arr[] = {10, 20, 30};
        MutableArraySequence<int> seq(arr, 3);

        Option<int> result = seq.TryGet(1);
        CHECK(result.IsSome() == true, "TryGet success: IsSome should be true");
        CHECK(result.Get() == 20, "TryGet success: Get should return 20");
        CHECK(result.GetOrElse(-1) == 20, "TryGet success: GetOrElse should return 20");
        TEST_OK("TryGet (element found)");
    }

    // ----------------------------------------------------------------------
    // Тест 12: TryGet (неудача)
    // ----------------------------------------------------------------------
    {
        int arr[] = {10, 20, 30};
        MutableArraySequence<int> seq(arr, 3);

        Option<int> result = seq.TryGet(5);
        CHECK(result.IsSome() == false, "TryGet fail: IsSome should be false");
        CHECK(result.IsNone() == true, "TryGet fail: IsNone should be true");
        CHECK(result.GetOrElse(-1) == -1, "TryGet fail: GetOrElse should return default");
        TEST_OK("TryGet (element not found)");
    }

    // ----------------------------------------------------------------------
    // Тест 13: TryGetFirst / TryGetLast
    // ----------------------------------------------------------------------
    {
        int arr[] = {10, 20, 30};
        MutableArraySequence<int> seq(arr, 3);

        Option<int> first = seq.TryGetFirst();
        CHECK(first.IsSome() == true, "TryGetFirst: IsSome should be true");
        CHECK(first.Get() == 10, "TryGetFirst: Get should return 10");

        Option<int> last = seq.TryGetLast();
        CHECK(last.IsSome() == true, "TryGetLast: IsSome should be true");
        CHECK(last.Get() == 30, "TryGetLast: Get should return 30");
        TEST_OK("TryGetFirst and TryGetLast");
    }

    // ----------------------------------------------------------------------
    // Тест 14: TryGetFirst на пустой
    // ----------------------------------------------------------------------
    {
        MutableArraySequence<int> seq;

        Option<int> first = seq.TryGetFirst();
        CHECK(first.IsSome() == false, "TryGetFirst empty: IsSome should be false");
        CHECK(first.IsNone() == true, "TryGetFirst empty: IsNone should be true");

        Option<int> last = seq.TryGetLast();
        CHECK(last.IsSome() == false, "TryGetLast empty: IsSome should be false");
        CHECK(last.IsNone() == true, "TryGetLast empty: IsNone should be true");
        TEST_OK("TryGetFirst/Last on empty sequence");
    }

    // ----------------------------------------------------------------------
    // Тест 15: Mutable — меняет оригинал
    // ----------------------------------------------------------------------
    {
        int arr[] = {1, 2, 3};
        MutableArraySequence<int> seq(arr, 3);

        seq.Append(4);
        CHECK(seq.GetLength() == 4, "Mutable Append: length should be 4");
        CHECK(seq.Get(3) == 4, "Mutable Append: seq[3] should be 4");
        TEST_OK("Mutable — changes original");
    }

    // ----------------------------------------------------------------------
    // Тест 16: Immutable — НЕ меняет оригинал
    // ----------------------------------------------------------------------
    {
        int arr[] = {1, 2, 3};
        ImmutableArraySequence<int> seq(arr, 3);

        Sequence<int>* newSeq = seq.Append(4);
        CHECK(seq.GetLength() == 3, "Immutable Append: original length should remain 3");
        CHECK(newSeq->GetLength() == 4, "Immutable Append: new length should be 4");
        CHECK(newSeq->Get(3) == 4, "Immutable Append: new seq[3] should be 4");
        CHECK(seq.Get(2) == 3, "Immutable Append: original seq[2] should remain 3");
        delete newSeq;
        TEST_OK("Immutable — does not change original");
    }

    // ----------------------------------------------------------------------
    // Тест 17: Immutable Prepend
    // ----------------------------------------------------------------------
    {
        int arr[] = {2, 3};
        ImmutableArraySequence<int> seq(arr, 2);

        Sequence<int>* newSeq = seq.Prepend(1);
        CHECK(seq.GetLength() == 2, "Immutable Prepend: original length should remain 2");
        CHECK(seq.Get(0) == 2, "Immutable Prepend: original seq[0] should remain 2");
        CHECK(newSeq->GetLength() == 3, "Immutable Prepend: new length should be 3");
        CHECK(newSeq->Get(0) == 1, "Immutable Prepend: new seq[0] should be 1");
        delete newSeq;
        TEST_OK("Immutable Prepend");
    }

    std::cout << std::endl << "=== ArraySequence TESTS PASSED ===" << std::endl;
    return 0;
}