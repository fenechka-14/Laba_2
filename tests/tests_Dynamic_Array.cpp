#include "../headers/Dynamic_Array.h"
#include <iostream>

// Макрос для проверки условия (теперь возвращает 1 при ошибке)
#define CHECK(condition, message) \
    if (!(condition)) { \
        std::cout << "[FAIL] " << message << std::endl; \
        return 1; \
    }

// Макрос для успешного теста
#define TEST_OK(name) \
    std::cout << "[OK] " << name << std::endl;
int main_Dynamic_Array() {
    // ----------------------------------------------------------------------
    // Тест 1: Конструктор по умолчанию
    // ----------------------------------------------------------------------
    {
        Dynamic_Array<int> arr;
        CHECK(arr.GetSize() == 0, "Default constructor: size should be 0");
        CHECK(arr.GetCapacity() == 1, "Default constructor: capacity should be 1");
        TEST_OK("Constructor default (empty array)");
    }

    // ----------------------------------------------------------------------
    // Тест 2: Конструктор с заданным размером
    // ----------------------------------------------------------------------
    {
        Dynamic_Array<int> arr(5);
        CHECK(arr.GetSize() == 5, "Constructor with size: size should be 5");
        CHECK(arr.GetCapacity() == 5, "Constructor with size: capacity should be 5");
        TEST_OK("Constructor with given size");
    }

    // ----------------------------------------------------------------------
    // Тест 3: Конструктор из существующего массива
    // ----------------------------------------------------------------------
    {
        int items[] = {10, 20, 30, 40, 50};
        Dynamic_Array<int> arr(items, 5);
        CHECK(arr.GetSize() == 5, "Array constructor: size should be 5");
        CHECK(arr[0] == 10, "Array constructor: arr[0] should be 10");
        CHECK(arr[2] == 30, "Array constructor: arr[2] should be 30");
        CHECK(arr[4] == 50, "Array constructor: arr[4] should be 50");
        TEST_OK("Constructor from existing array");
    }

    // ----------------------------------------------------------------------
    // Тест 4: Копирующий конструктор
    // ----------------------------------------------------------------------
    {
        int items[] = {1, 2, 3};
        Dynamic_Array<int> arr1(items, 3);
        Dynamic_Array<int> arr2(arr1);

        CHECK(arr2.GetSize() == 3, "Copy constructor: size should be 3");
        CHECK(arr2[0] == 1, "Copy constructor: arr2[0] should be 1");
        CHECK(arr2[1] == 2, "Copy constructor: arr2[1] should be 2");
        CHECK(arr2[2] == 3, "Copy constructor: arr2[2] should be 3");

        // Проверка глубокого копирования
        arr1[0] = 99;
        CHECK(arr2[0] == 1, "Copy constructor: deep copy - arr2[0] should remain 1");
        TEST_OK("Copy constructor (deep copy)");
    }

    // ----------------------------------------------------------------------
    // Тест 5: Оператор присваивания
    // ----------------------------------------------------------------------
    {
        int items[] = {5, 6, 7};
        Dynamic_Array<int> arr1(items, 3);
        Dynamic_Array<int> arr2;
        arr2 = arr1;

        CHECK(arr2.GetSize() == 3, "Assignment: size should be 3");
        CHECK(arr2[0] == 5, "Assignment: arr2[0] should be 5");
        CHECK(arr2[1] == 6, "Assignment: arr2[1] should be 6");
        CHECK(arr2[2] == 7, "Assignment: arr2[2] should be 7");

        // Глубокое копирование
        arr1[0] = 99;
        CHECK(arr2[0] == 5, "Assignment: deep copy - arr2[0] should remain 5");

        // Самоприсваивание
        arr2 = arr2;
        CHECK(arr2.GetSize() == 3, "Assignment: self-assign - size should remain 3");
        CHECK(arr2[0] == 5, "Assignment: self-assign - arr2[0] should remain 5");
        TEST_OK("Assignment operator");
    }

    // ----------------------------------------------------------------------
    // Тест 6: Доступ к элементам через operator[]
    // ----------------------------------------------------------------------
    {
        int items[] = {100, 200, 300};
        Dynamic_Array<int> arr(items, 3);

        CHECK(arr[0] == 100, "operator[] read: arr[0] should be 100");
        CHECK(arr[1] == 200, "operator[] read: arr[1] should be 200");
        CHECK(arr[2] == 300, "operator[] read: arr[2] should be 300");

        arr[0] = 111;
        CHECK(arr[0] == 111, "operator[] write: arr[0] should be 111");

        arr[1] = 222;
        CHECK(arr[1] == 222, "operator[] write: arr[1] should be 222");
        TEST_OK("Element access via operator[]");
    }

    // ----------------------------------------------------------------------
    // Тест 7: Доступ через Get и Set
    // ----------------------------------------------------------------------
    {
        int items[] = {10, 20, 30};
        Dynamic_Array<int> arr(items, 3);

        CHECK(arr.Get(0) == 10, "Get: arr.Get(0) should be 10");
        CHECK(arr.Get(1) == 20, "Get: arr.Get(1) should be 20");
        CHECK(arr.Get(2) == 30, "Get: arr.Get(2) should be 30");

        arr.Set(0, 15);
        CHECK(arr.Get(0) == 15, "Set: after Set(0, 15), Get(0) should be 15");

        arr.Set(2, 35);
        CHECK(arr.Get(2) == 35, "Set: after Set(2, 35), Get(2) should be 35");
        TEST_OK("Element access via Get/Set");
    }

    // ----------------------------------------------------------------------
    // Тест 8: Константный доступ
    // ----------------------------------------------------------------------
    {
        int items[] = {7, 8, 9};
        const Dynamic_Array<int> arr(items, 3);

        CHECK(arr[0] == 7, "const operator[]: arr[0] should be 7");
        CHECK(arr.Get(1) == 8, "const Get: arr.Get(1) should be 8");
        CHECK(arr[2] == 9, "const operator[]: arr[2] should be 9");
        TEST_OK("Const element access");
    }

    // ----------------------------------------------------------------------
    // Тест 9: Resize - увеличение с перевыделением (ОТЛАДКА 2)
    // ----------------------------------------------------------------------
    {
        int items[] = {1, 2, 3};
        Dynamic_Array<int> arr(items, 3);

        arr.Resize(5);

        CHECK(arr.GetSize() == 5, "Resize increase: size should be 5");
        CHECK(arr[0] == 1, "Resize increase: arr[0] should remain 1");
        CHECK(arr[1] == 2, "Resize increase: arr[1] should remain 2");
        CHECK(arr[2] == 3, "Resize increase: arr[2] should remain 3");
        CHECK(arr[3] == 0, "Resize increase: arr[3] should be default 0");
        CHECK(arr[4] == 0, "Resize increase: arr[4] should be default 0");
        TEST_OK("Resize (increase with reallocation)");
    }
    // ----------------------------------------------------------------------
    // Тест 10: Resize - увеличение без перевыделения
    // ----------------------------------------------------------------------
    {
        Dynamic_Array<int> arr(2);
        arr[0] = 10;
        arr[1] = 20;

        arr.Resize(4);   // capacity станет 8 (4*2)
        int cap_before = arr.GetCapacity();  // запоминаем ёмкость (8)

        arr.Resize(5);   // увеличиваем до 5, capacity=8 хватает
        CHECK(arr.GetCapacity() == cap_before, "Resize no-realloc: capacity should not change");

        arr.Resize(7);   // увеличиваем до 7, capacity=8 хватает
        CHECK(arr.GetCapacity() == cap_before, "Resize no-realloc: capacity should not change");

        CHECK(arr.GetSize() == 7, "Resize no-realloc: size should be 7");
        CHECK(arr[0] == 10, "Resize no-realloc: arr[0] should remain 10");
        CHECK(arr[1] == 20, "Resize no-realloc: arr[1] should remain 20");
        CHECK(arr[5] == 0, "Resize no-realloc: arr[5] should be default 0");
        CHECK(arr[6] == 0, "Resize no-realloc: arr[6] should be default 0");
        TEST_OK("Resize (increase without reallocation)");
    }
    // ----------------------------------------------------------------------
    // Тест 11: Resize - уменьшение
    // ----------------------------------------------------------------------
    {
        int items[] = {1, 2, 3, 4, 5};
        Dynamic_Array<int> arr(items, 5);

        arr.Resize(3);
        CHECK(arr.GetSize() == 3, "Resize decrease: size should be 3");
        CHECK(arr[0] == 1, "Resize decrease: arr[0] should be 1");
        CHECK(arr[1] == 2, "Resize decrease: arr[1] should be 2");
        CHECK(arr[2] == 3, "Resize decrease: arr[2] should be 3");
        CHECK(arr.GetCapacity() == 5, "Resize decrease: capacity should remain 5");
        TEST_OK("Resize (decrease)");
    }

    // ----------------------------------------------------------------------
    // Тест 12: Исключение IndexOutOfRangeException
    // ----------------------------------------------------------------------
    {
        Dynamic_Array<int> arr(3);
        bool caught = false;

        try { arr[5]; }
        catch (const IndexOutOfRangeException&) { caught = true; }
        CHECK(caught, "IndexOutOfRange: should throw on index >= size");

        caught = false;
        try { arr.Get(-1); }
        catch (const IndexOutOfRangeException&) { caught = true; }
        CHECK(caught, "IndexOutOfRange: should throw on negative index");

        caught = false;
        try { arr.Set(3, 100); }
        catch (const IndexOutOfRangeException&) { caught = true; }
        CHECK(caught, "IndexOutOfRange: should throw on Set with index == size");

        TEST_OK("IndexOutOfRangeException");
    }

    // ----------------------------------------------------------------------
    // Тест 13: Исключение InvalidArgumentException
    // ----------------------------------------------------------------------
    {
        bool caught = false;

        try { Dynamic_Array<int> arr(-5); }
        catch (const InvalidArgumentException&) { caught = true; }
        CHECK(caught, "InvalidArgument: negative size in constructor");

        caught = false;
        int items[] = {1, 2};
        try { Dynamic_Array<int> arr(items, -2); }
        catch (const InvalidArgumentException&) { caught = true; }
        CHECK(caught, "InvalidArgument: negative count in array constructor");

        caught = false;
        Dynamic_Array<int> arr(5);
        try { arr.Resize(-3); }
        catch (const InvalidArgumentException&) { caught = true; }
        CHECK(caught, "InvalidArgument: negative new_size in Resize");

        TEST_OK("InvalidArgumentException");
    }

    // ----------------------------------------------------------------------
    // Тест 14: Итераторы Begin/End
    // ----------------------------------------------------------------------
    {
        int items[] = {10, 20, 30, 40, 50};
        Dynamic_Array<int> arr(items, 5);

        int expected[] = {10, 20, 30, 40, 50};
        int idx = 0;
        for (int* it = arr.Begin(); it != arr.End(); ++it) {
            if (*it != expected[idx]) {
                std::cout << "[FAIL] Iterator: element mismatch at index " << idx << std::endl;
                return 1;
            }
            ++idx;
        }
        CHECK(idx == 5, "Iterator: should iterate 5 times");
        TEST_OK("Iterators Begin/End");
    }

    // ----------------------------------------------------------------------
    // Тест 15: Константные итераторы
    // ----------------------------------------------------------------------
    {
        int items[] = {1, 2, 3};
        const Dynamic_Array<int> arr(items, 3);

        int sum = 0;
        for (const int* it = arr.Begin(); it != arr.End(); ++it) {
            sum += *it;
        }
        CHECK(sum == 6, "Const iterators: sum should be 6");
        TEST_OK("Const iterators");
    }

    // ----------------------------------------------------------------------
    // Тест 16: Изменение элементов через итератор
    // ----------------------------------------------------------------------
    {
        int items[] = {1, 2, 3};
        Dynamic_Array<int> arr(items, 3);

        for (int* it = arr.Begin(); it != arr.End(); ++it) {
            *it = (*it) * 10;
        }
        CHECK(arr[0] == 10, "Modify via iterator: arr[0] should be 10");
        CHECK(arr[1] == 20, "Modify via iterator: arr[1] should be 20");
        CHECK(arr[2] == 30, "Modify via iterator: arr[2] should be 30");
        TEST_OK("Modify elements through iterator");
    }

    // ----------------------------------------------------------------------
    // Тест 17: GetCapacity
    // ----------------------------------------------------------------------
    {
        Dynamic_Array<int> arr(10);
        CHECK(arr.GetCapacity() == 10, "GetCapacity: initial should be 10");

        arr.Resize(5);
        CHECK(arr.GetCapacity() == 10, "GetCapacity: after decrease should remain 10");

        arr.Resize(15);
        CHECK(arr.GetCapacity() == 30, "GetCapacity: after increase should be 30 (15*2)");
        TEST_OK("GetCapacity");
    }

    // ----------------------------------------------------------------------
    // Тест 18: Пустой массив и Resize
    // ----------------------------------------------------------------------
    {
        Dynamic_Array<int> arr;
        CHECK(arr.GetSize() == 0, "Empty array: initial size should be 0");
        CHECK(arr.GetCapacity() == 1, "Empty array: initial capacity should be 1");

        arr.Resize(3);
        CHECK(arr.GetSize() == 3, "Empty array: after resize size should be 3");
        CHECK(arr[0] == 0, "Empty array: arr[0] should be default 0");
        CHECK(arr[1] == 0, "Empty array: arr[1] should be default 0");
        CHECK(arr[2] == 0, "Empty array: arr[2] should be default 0");
        TEST_OK("Empty array Resize");
    }

    // ----------------------------------------------------------------------
    // Тест 19: Многократные Resize вверх-вниз
    // ----------------------------------------------------------------------
    {
        Dynamic_Array<int> arr;
        arr.Resize(10);
        for (int i = 0; i < 10; ++i) arr[i] = i * 10;
        arr.Resize(5);
        arr.Resize(8);

        CHECK(arr.GetSize() == 8, "Multiple Resize: size should be 8");
        CHECK(arr[0] == 0, "Multiple Resize: arr[0] should be 0");
        CHECK(arr[4] == 40, "Multiple Resize: arr[4] should be 40");
        CHECK(arr[5] == 0, "Multiple Resize: arr[5] should be default 0");
        CHECK(arr[7] == 0, "Multiple Resize: arr[7] should be default 0");
        TEST_OK("Multiple Resize up and down");
    }

        // ----------------------------------------------------------------------
    // Тест 20: TryGet (успех)
    // ----------------------------------------------------------------------
    {
        int items[] = {10, 20, 30};
        Dynamic_Array<int> arr(items, 3);

        Option<int> result = arr.TryGet(1);
        CHECK(result.IsSome() == true, "TryGet success: IsSome should be true");
        CHECK(result.IsNone() == false, "TryGet success: IsNone should be false");
        CHECK(result.Get() == 20, "TryGet success: Get should return 20");
        CHECK(result.GetOrElse(-1) == 20, "TryGet success: GetOrElse should return 20");
        TEST_OK("TryGet (element found)");
    }

    // ----------------------------------------------------------------------
    // Тест 21: TryGet (неудача)
    // ----------------------------------------------------------------------
    {
        int items[] = {10, 20, 30};
        Dynamic_Array<int> arr(items, 3);

        Option<int> result = arr.TryGet(5);
        CHECK(result.IsSome() == false, "TryGet fail: IsSome should be false");
        CHECK(result.IsNone() == true, "TryGet fail: IsNone should be true");
        CHECK(result.GetOrElse(-1) == -1, "TryGet fail: GetOrElse should return default");
        TEST_OK("TryGet (element not found)");
    }

    // ----------------------------------------------------------------------
    // Тест 22: TryGet с отрицательным индексом
    // ----------------------------------------------------------------------
    {
        int items[] = {10, 20, 30};
        Dynamic_Array<int> arr(items, 3);

        Option<int> result = arr.TryGet(-1);
        CHECK(result.IsSome() == false, "TryGet negative: IsSome should be false");
        CHECK(result.IsNone() == true, "TryGet negative: IsNone should be true");
        CHECK(result.GetOrElse(0) == 0, "TryGet negative: GetOrElse should return default");
        TEST_OK("TryGet (negative index)");
    }

    // ----------------------------------------------------------------------
    // Тест 23: Option GetOrElse
    // ----------------------------------------------------------------------
    {
        Option<int> some(42);
        CHECK(some.IsSome() == true, "Option some: IsSome should be true");
        CHECK(some.IsNone() == false, "Option some: IsNone should be false");
        CHECK(some.Get() == 42, "Option some: Get should return 42");
        CHECK(some.GetOrElse(0) == 42, "Option some: GetOrElse should return 42");

        Option<int> none;
        CHECK(none.IsSome() == false, "Option none: IsSome should be false");
        CHECK(none.IsNone() == true, "Option none: IsNone should be true");
        CHECK(none.GetOrElse(99) == 99, "Option none: GetOrElse should return default");
        TEST_OK("Option (Some and None)");
    }

    // ----------------------------------------------------------------------
    // Тест 24: RemoveAt из середины
    // ----------------------------------------------------------------------
    {
        int items[] = {10, 20, 30, 40, 50};
        Dynamic_Array<int> arr(items, 5);

        arr.RemoveAt(2);  // удаляем 30
        CHECK(arr.GetSize() == 4, "RemoveAt middle: size should be 4");
        CHECK(arr[0] == 10, "RemoveAt middle: arr[0] should be 10");
        CHECK(arr[1] == 20, "RemoveAt middle: arr[1] should be 20");
        CHECK(arr[2] == 40, "RemoveAt middle: arr[2] should be 40");
        CHECK(arr[3] == 50, "RemoveAt middle: arr[3] should be 50");
        TEST_OK("RemoveAt from middle");
    }

    // ----------------------------------------------------------------------
    // Тест 25: RemoveAt из начала
    // ----------------------------------------------------------------------
    {
        int items[] = {10, 20, 30};
        Dynamic_Array<int> arr(items, 3);

        arr.RemoveAt(0);
        CHECK(arr.GetSize() == 2, "RemoveAt first: size should be 2");
        CHECK(arr[0] == 20, "RemoveAt first: arr[0] should be 20");
        CHECK(arr[1] == 30, "RemoveAt first: arr[1] should be 30");
        TEST_OK("RemoveAt from beginning");
    }

    // ----------------------------------------------------------------------
    // Тест 26: RemoveAt из конца
    // ----------------------------------------------------------------------
    {
        int items[] = {10, 20, 30};
        Dynamic_Array<int> arr(items, 3);

        arr.RemoveAt(2);
        CHECK(arr.GetSize() == 2, "RemoveAt last: size should be 2");
        CHECK(arr[0] == 10, "RemoveAt last: arr[0] should be 10");
        CHECK(arr[1] == 20, "RemoveAt last: arr[1] should be 20");
        TEST_OK("RemoveAt from end");
    }

    std::cout << std::endl << "=== ALL TESTS PASSED ===" << std::endl;
    return 0;
}