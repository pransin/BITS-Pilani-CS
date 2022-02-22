#include "merge.h"
#include <stdio.h>

void mergeSort(Element records[], int size)
{
    if (size == 1 || size == 0)
        return;
    mergeSort(records, size / 2);
    mergeSort(records + size / 2, (size + 1) / 2);
    Element temp[size];
    merge(records, size / 2, records + size / 2, (size + 1) / 2, temp);
    for (int i = 0; i < size; i++)
    {
        printf("%d ", i);
        records[i] = temp[i];
    }
}