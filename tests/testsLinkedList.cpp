#include "../headers/LinkedList.h"
#include <iostream>

#define CHECK(condition, message) \
    if (!(condition)) { \
        std::cout << "[FAIL] " << message << std::endl; \
        return 1; \
    }

#define TEST_OK(name) \
    std::cout << "[OK] " << name << std::endl;

int main_LinkedList() {
    // ----------------------------------------------------------------------
    // Тест 1: Конструктор по умолчанию
    // ----------------------------------------------------------------------
    {
        LinkedList<int> list;
        CHECK(list.GetLength() == 0, "Default constructor: length should be 0");
        TEST_OK("Constructor default (empty list)");
    }

    // ----------------------------------------------------------------------
    // Тест 2: Конструктор из массива
    // ----------------------------------------------------------------------
    {
        int items[] = {10, 20, 30, 40, 50};
        LinkedList<int> list(items, 5);
        CHECK(list.GetLength() == 5, "Array constructor: length should be 5");
        CHECK(list[0] == 10, "Array constructor: list[0] should be 10");
        CHECK(list[2] == 30, "Array constructor: list[2] should be 30");
        CHECK(list[4] == 50, "Array constructor: list[4] should be 50");
        TEST_OK("Constructor from array");
    }

    // ----------------------------------------------------------------------
    // Тест 3: Копирующий конструктор
    // ----------------------------------------------------------------------
    {
        int items[] = {1, 2, 3};
        LinkedList<int> list1(items, 3);
        LinkedList<int> list2(list1);

        CHECK(list2.GetLength() == 3, "Copy constructor: length should be 3");
        CHECK(list2[0] == 1, "Copy constructor: list2[0] should be 1");
        CHECK(list2[1] == 2, "Copy constructor: list2[1] should be 2");
        CHECK(list2[2] == 3, "Copy constructor: list2[2] should be 3");

        // Проверка глубокого копирования
        list1[0] = 99;
        CHECK(list2[0] == 1, "Copy constructor: deep copy - list2[0] should remain 1");
        TEST_OK("Copy constructor (deep copy)");
    }

    // ----------------------------------------------------------------------
    // Тест 4: Оператор присваивания
    // ----------------------------------------------------------------------
    {
        int items[] = {5, 6, 7};
        LinkedList<int> list1(items, 3);
        LinkedList<int> list2;
        list2 = list1;

        CHECK(list2.GetLength() == 3, "Assignment: length should be 3");
        CHECK(list2[0] == 5, "Assignment: list2[0] should be 5");
        CHECK(list2[1] == 6, "Assignment: list2[1] should be 6");
        CHECK(list2[2] == 7, "Assignment: list2[2] should be 7");

        // Глубокое копирование
        list1[0] = 99;
        CHECK(list2[0] == 5, "Assignment: deep copy - list2[0] should remain 5");

        // Самоприсваивание
        list2 = list2;
        CHECK(list2.GetLength() == 3, "Assignment: self-assign - length should remain 3");
        CHECK(list2[0] == 5, "Assignment: self-assign - list2[0] should remain 5");
        TEST_OK("Assignment operator");
    }

    // ----------------------------------------------------------------------
    // Тест 5: Доступ к элементам через operator[]
    // ----------------------------------------------------------------------
    {
        int items[] = {100, 200, 300};
        LinkedList<int> list(items, 3);

        CHECK(list[0] == 100, "operator[] read: list[0] should be 100");
        CHECK(list[1] == 200, "operator[] read: list[1] should be 200");
        CHECK(list[2] == 300, "operator[] read: list[2] should be 300");

        list[0] = 111;
        CHECK(list[0] == 111, "operator[] write: list[0] should be 111");

        list[1] = 222;
        CHECK(list[1] == 222, "operator[] write: list[1] should be 222");
        TEST_OK("Element access via operator[]");
    }

    // ----------------------------------------------------------------------
    // Тест 6: Доступ через Get
    // ----------------------------------------------------------------------
    {
        int items[] = {10, 20, 30};
        LinkedList<int> list(items, 3);

        CHECK(list.Get(0) == 10, "Get: list.Get(0) should be 10");
        CHECK(list.Get(1) == 20, "Get: list.Get(1) should be 20");
        CHECK(list.Get(2) == 30, "Get: list.Get(2) should be 30");
        TEST_OK("Element access via Get");
    }

    // ----------------------------------------------------------------------
    // Тест 7: GetFirst и GetLast
    // ----------------------------------------------------------------------
    {
        int items[] = {10, 20, 30};
        LinkedList<int> list(items, 3);

        CHECK(list.GetFirst() == 10, "GetFirst: should be 10");
        CHECK(list.GetLast() == 30, "GetLast: should be 30");

        list.GetFirst() = 99;
        CHECK(list.GetFirst() == 99, "GetFirst write: should be 99");

        list.GetLast() = 77;
        CHECK(list.GetLast() == 77, "GetLast write: should be 77");
        TEST_OK("GetFirst and GetLast");
    }

    // ----------------------------------------------------------------------
    // Тест 8: Константный доступ
    // ----------------------------------------------------------------------
    {
        int items[] = {7, 8, 9};
        const LinkedList<int> list(items, 3);

        CHECK(list[0] == 7, "const operator[]: list[0] should be 7");
        CHECK(list.Get(1) == 8, "const Get: list.Get(1) should be 8");
        CHECK(list.GetFirst() == 7, "const GetFirst: should be 7");
        CHECK(list.GetLast() == 9, "const GetLast: should be 9");
        TEST_OK("Const element access");
    }

    // ----------------------------------------------------------------------
    // Тест 9: Append
    // ----------------------------------------------------------------------
    {
        LinkedList<int> list;
        list.Append(10);
        CHECK(list.GetLength() == 1, "Append: length should be 1");
        CHECK(list[0] == 10, "Append: list[0] should be 10");

        list.Append(20);
        CHECK(list.GetLength() == 2, "Append: length should be 2");
        CHECK(list[1] == 20, "Append: list[1] should be 20");

        list.Append(30);
        CHECK(list.GetLength() == 3, "Append: length should be 3");
        CHECK(list[2] == 30, "Append: list[2] should be 30");

        // Проверка порядка
        CHECK(list[0] == 10, "Append: order - list[0] should be 10");
        CHECK(list[1] == 20, "Append: order - list[1] should be 20");
        CHECK(list[2] == 30, "Append: order - list[2] should be 30");
        TEST_OK("Append");
    }

    // ----------------------------------------------------------------------
    // Тест 10: Prepend
    // ----------------------------------------------------------------------
    {
        LinkedList<int> list;
        list.Prepend(30);
        CHECK(list.GetLength() == 1, "Prepend: length should be 1");
        CHECK(list[0] == 30, "Prepend: list[0] should be 30");

        list.Prepend(20);
        CHECK(list.GetLength() == 2, "Prepend: length should be 2");
        CHECK(list[0] == 20, "Prepend: list[0] should be 20");
        CHECK(list[1] == 30, "Prepend: list[1] should be 30");

        list.Prepend(10);
        CHECK(list.GetLength() == 3, "Prepend: length should be 3");
        CHECK(list[0] == 10, "Prepend: list[0] should be 10");
        CHECK(list[1] == 20, "Prepend: list[1] should be 20");
        CHECK(list[2] == 30, "Prepend: list[2] should be 30");
        TEST_OK("Prepend");
    }

    // ----------------------------------------------------------------------
    // Тест 11: InsertAt
    // ----------------------------------------------------------------------
    {
        int items[] = {10, 30, 40};
        LinkedList<int> list(items, 3);

        // Вставка в середину
        list.InsertAt(20, 1);
        CHECK(list.GetLength() == 4, "InsertAt middle: length should be 4");
        CHECK(list[0] == 10, "InsertAt middle: list[0] should be 10");
        CHECK(list[1] == 20, "InsertAt middle: list[1] should be 20");
        CHECK(list[2] == 30, "InsertAt middle: list[2] should be 30");
        CHECK(list[3] == 40, "InsertAt middle: list[3] should be 40");

        // Вставка в начало
        list.InsertAt(5, 0);
        CHECK(list.GetLength() == 5, "InsertAt beginning: length should be 5");
        CHECK(list[0] == 5, "InsertAt beginning: list[0] should be 5");
        CHECK(list[1] == 10, "InsertAt beginning: list[1] should be 10");

        // Вставка в конец
        list.InsertAt(50, list.GetLength());
        CHECK(list.GetLength() == 6, "InsertAt end: length should be 6");
        CHECK(list[5] == 50, "InsertAt end: list[5] should be 50");
        TEST_OK("InsertAt");
    }

    // ----------------------------------------------------------------------
    // Тест 12: GetSubList
    // ----------------------------------------------------------------------
    {
        int items[] = {10, 20, 30, 40, 50};
        LinkedList<int> list(items, 5);

        // Подсписок с середины
        LinkedList<int> sub1 = list.GetSubList(1, 3);
        CHECK(sub1.GetLength() == 3, "GetSubList middle: length should be 3");
        CHECK(sub1[0] == 20, "GetSubList middle: sub1[0] should be 20");
        CHECK(sub1[1] == 30, "GetSubList middle: sub1[1] should be 30");
        CHECK(sub1[2] == 40, "GetSubList middle: sub1[2] should be 40");

        // Подсписок с начала
        LinkedList<int> sub2 = list.GetSubList(0, 2);
        CHECK(sub2.GetLength() == 3, "GetSubList beginning: length should be 3");
        CHECK(sub2[0] == 10, "GetSubList beginning: sub2[0] should be 10");
        CHECK(sub2[2] == 30, "GetSubList beginning: sub2[2] should be 30");

        // Подсписок до конца
        LinkedList<int> sub3 = list.GetSubList(3, 4);
        CHECK(sub3.GetLength() == 2, "GetSubList end: length should be 2");
        CHECK(sub3[0] == 40, "GetSubList end: sub3[0] should be 40");
        CHECK(sub3[1] == 50, "GetSubList end: sub3[1] should be 50");

        // Подсписок не зависит от оригинала
        list[0] = 99;
        CHECK(sub2[0] == 10, "GetSubList independence: sub2[0] should remain 10");
        TEST_OK("GetSubList");
    }

    // ----------------------------------------------------------------------
    // Тест 13: Concat
    // ----------------------------------------------------------------------
    {
        int items1[] = {1, 2, 3};
        int items2[] = {4, 5};
        LinkedList<int> list1(items1, 3);
        LinkedList<int> list2(items2, 2);

        LinkedList<int>* result = list1.Concat(&list2);
        CHECK(result->GetLength() == 5, "Concat: length should be 5");
        CHECK((*result)[0] == 1, "Concat: result[0] should be 1");
        CHECK((*result)[1] == 2, "Concat: result[1] should be 2");
        CHECK((*result)[2] == 3, "Concat: result[2] should be 3");
        CHECK((*result)[3] == 4, "Concat: result[3] should be 4");
        CHECK((*result)[4] == 5, "Concat: result[4] should be 5");

        // Исходные списки не изменились
        CHECK(list1.GetLength() == 3, "Concat: original list1 should not change");
        CHECK(list2.GetLength() == 2, "Concat: original list2 should not change");

        delete result;
        TEST_OK("Concat");
    }

    // ----------------------------------------------------------------------
    // Тест 14: GetLength
    // ----------------------------------------------------------------------
    {
        LinkedList<int> list;
        CHECK(list.GetLength() == 0, "GetLength: empty should be 0");

        list.Append(1);
        CHECK(list.GetLength() == 1, "GetLength: after Append should be 1");

        list.Append(2);
        CHECK(list.GetLength() == 2, "GetLength: after another Append should be 2");
        TEST_OK("GetLength");
    }

    // ----------------------------------------------------------------------
    // Тест 15: IndexOutOfRangeException
    // ----------------------------------------------------------------------
    {
        LinkedList<int> list;
        list.Append(1);
        list.Append(2);
        list.Append(3);

        bool caught = false;

        try { list[5]; }
        catch (const IndexOutOfRangeException&) { caught = true; }
        CHECK(caught, "IndexOutOfRange: should throw on index >= length");

        caught = false;
        try { list.Get(-1); }
        catch (const IndexOutOfRangeException&) { caught = true; }
        CHECK(caught, "IndexOutOfRange: should throw on negative index");

        caught = false;
        try { list.InsertAt(10, 10); }
        catch (const IndexOutOfRangeException&) { caught = true; }
        CHECK(caught, "IndexOutOfRange: should throw on InsertAt with invalid index");

        TEST_OK("IndexOutOfRangeException");
    }

    // ----------------------------------------------------------------------
    // Тест 16: InvalidArgumentException
    // ----------------------------------------------------------------------
    {
        bool caught = false;

        int items[] = {1, 2};
        try { LinkedList<int> list(items, -2); }
        catch (const InvalidArgumentException&) { caught = true; }
        CHECK(caught, "InvalidArgument: negative count in constructor");

        TEST_OK("InvalidArgumentException");
    }

    // ----------------------------------------------------------------------
    // Тест 17: EmptyStructerException
    // ----------------------------------------------------------------------
    {
        LinkedList<int> list;
        bool caught = false;

        try { list.GetFirst(); }
        catch (const EmptyStructerException&) { caught = true; }
        CHECK(caught, "EmptyStructer: GetFirst on empty list");

        caught = false;
        try { list.GetLast(); }
        catch (const EmptyStructerException&) { caught = true; }
        CHECK(caught, "EmptyStructer: GetLast on empty list");

        TEST_OK("EmptyStructerException");
    }

    // ----------------------------------------------------------------------
    // Тест 18: Итераторы
    // ----------------------------------------------------------------------
    {
        int items[] = {10, 20, 30, 40, 50};
        LinkedList<int> list(items, 5);

        int expected[] = {10, 20, 30, 40, 50};
        int idx = 0;
        for (auto it = list.Begin(); it != list.End(); ++it) {
            if (*it != expected[idx]) {
                std::cout << "[FAIL] Iterator: element mismatch at index " << idx << std::endl;
                return 1;
            }
            ++idx;
        }
        CHECK(idx == 5, "Iterator: should iterate 5 times");
        TEST_OK("Iterators");
    }

    // ----------------------------------------------------------------------
    // Тест 19: Изменение через итератор
    // ----------------------------------------------------------------------
    {
        int items[] = {1, 2, 3};
        LinkedList<int> list(items, 3);

        for (auto it = list.Begin(); it != list.End(); ++it) {
            *it = (*it) * 10;
        }
        CHECK(list[0] == 10, "Modify via iterator: list[0] should be 10");
        CHECK(list[1] == 20, "Modify via iterator: list[1] should be 20");
        CHECK(list[2] == 30, "Modify via iterator: list[2] should be 30");
        TEST_OK("Modify through iterator");
    }

    // ----------------------------------------------------------------------
    // Тест 20: Смешанные операции
    // ----------------------------------------------------------------------
    {
        LinkedList<int> list;

        list.Append(2);
        list.Prepend(1);
        list.Append(3);

        CHECK(list.GetLength() == 3, "Mixed: length should be 3");
        CHECK(list[0] == 1, "Mixed: list[0] should be 1");
        CHECK(list[1] == 2, "Mixed: list[1] should be 2");
        CHECK(list[2] == 3, "Mixed: list[2] should be 3");
        TEST_OK("Mixed Append and Prepend");
    }

    // ----------------------------------------------------------------------
    // Тест 21: TryGet (успех)
    // ----------------------------------------------------------------------
    {
        int items[] = {10, 20, 30};
        LinkedList<int> list(items, 3);

        Option<int> result = list.TryGet(1);
        CHECK(result.IsSome() == true, "TryGet success: IsSome should be true");
        CHECK(result.IsNone() == false, "TryGet success: IsNone should be false");
        CHECK(result.Get() == 20, "TryGet success: Get should return 20");
        CHECK(result.GetOrElse(-1) == 20, "TryGet success: GetOrElse should return 20");
        TEST_OK("TryGet (element found)");
    }

    // ----------------------------------------------------------------------
    // Тест 22: TryGet (неудача)
    // ----------------------------------------------------------------------
    {
        int items[] = {10, 20, 30};
        LinkedList<int> list(items, 3);

        Option<int> result = list.TryGet(5);
        CHECK(result.IsSome() == false, "TryGet fail: IsSome should be false");
        CHECK(result.IsNone() == true, "TryGet fail: IsNone should be true");
        CHECK(result.GetOrElse(-1) == -1, "TryGet fail: GetOrElse should return default");
        TEST_OK("TryGet (element not found)");
    }

    // ----------------------------------------------------------------------
    // Тест 23: TryGet с отрицательным индексом
    // ----------------------------------------------------------------------
    {
        int items[] = {10, 20, 30};
        LinkedList<int> list(items, 3);

        Option<int> result = list.TryGet(-1);
        CHECK(result.IsSome() == false, "TryGet negative: IsSome should be false");
        CHECK(result.IsNone() == true, "TryGet negative: IsNone should be true");
        CHECK(result.GetOrElse(0) == 0, "TryGet negative: GetOrElse should return default");
        TEST_OK("TryGet (negative index)");
    }

    // ----------------------------------------------------------------------
    // Тест 24: RemoveAt из середины
    // ----------------------------------------------------------------------
    {
        int items[] = {10, 20, 30, 40, 50};
        LinkedList<int> list(items, 5);

        list.RemoveAt(2);
        CHECK(list.GetLength() == 4, "RemoveAt middle: length should be 4");
        CHECK(list[0] == 10, "RemoveAt middle: list[0] should be 10");
        CHECK(list[1] == 20, "RemoveAt middle: list[1] should be 20");
        CHECK(list[2] == 40, "RemoveAt middle: list[2] should be 40");
        CHECK(list[3] == 50, "RemoveAt middle: list[3] should be 50");
        TEST_OK("RemoveAt from middle");
    }

    // ----------------------------------------------------------------------
    // Тест 25: RemoveAt из начала
    // ----------------------------------------------------------------------
    {
        int items[] = {10, 20, 30};
        LinkedList<int> list(items, 3);

        list.RemoveAt(0);
        CHECK(list.GetLength() == 2, "RemoveAt first: length should be 2");
        CHECK(list[0] == 20, "RemoveAt first: list[0] should be 20");
        CHECK(list[1] == 30, "RemoveAt first: list[1] should be 30");
        TEST_OK("RemoveAt from beginning");
    }

    // ----------------------------------------------------------------------
    // Тест 26: RemoveAt из конца
    // ----------------------------------------------------------------------
    {
        int items[] = {10, 20, 30};
        LinkedList<int> list(items, 3);

        list.RemoveAt(2);
        CHECK(list.GetLength() == 2, "RemoveAt last: length should be 2");
        CHECK(list[0] == 10, "RemoveAt last: list[0] should be 10");
        CHECK(list[1] == 20, "RemoveAt last: list[1] should be 20");
        TEST_OK("RemoveAt from end");
    }

    std::cout << std::endl << "=== ALL TESTS PASSED ===" << std::endl;
    return 0;
}