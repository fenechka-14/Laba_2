int main_DynamicArray();

int main_LinkedList();

int main_ArraySequence();

int main_BitSequence();

int main_ListSequence();

int main() {
    int result1 = main_DynamicArray();
    int result2 = main_LinkedList();
    int result3 = main_ArraySequence();
    int result4 = main_BitSequence();
    int result5 = main_ListSequence();

    if (result1 == 0 && result2 == 0 && result3 == 0 && result4 == 0 && result5 == 0) {
        return 0;
    }
    return 1;
}
