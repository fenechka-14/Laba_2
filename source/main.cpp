#include "scanValues.h"
#include "menu.h"
#include "SequenceOperations.h"

int main() {
    printBanner();

    int typeChoice;
    do { printTypeMenu(); } while (!scanInt(typeChoice) || typeChoice < 1 || typeChoice > 2);

    switch (typeChoice) {
        case 1: runMenu<int>();  break;
        case 2: runMenu<bool>(); break;
    }
    return 0;
}