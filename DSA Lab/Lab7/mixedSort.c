#include "insertionsort.h"
#include "quicksort.h"

void mixedSort(Employee empArr[], int size, int S){
    quickSort(empArr, size, S);
    insertionSort(empArr, size);
}