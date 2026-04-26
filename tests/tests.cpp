// Запуск функции main из test_Dynamic_Array.cpp
int main_Dynamic_Array();

// Запуск функции main из test_Linked_List.cpp
int main_Linked_List();

int main() {
    int result1 = main_Dynamic_Array();
    int result2 = main_Linked_List();

    if (result1 == 0 && result2 == 0) {
        return 0;
    }
    return 1;
}
