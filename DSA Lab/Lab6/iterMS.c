#include "merge.h"


void mergeSort(Element records[], int size)
{
    for (int currsize = 1; currsize < size; currsize *= 2)
    {
        Element Ls[2 * currsize];
        for (int start = 0; start < size; start += 2 * currsize)
        {
            int mid = min(start + currsize, size - 1);
            int end = min(mid + currsize, size - 1);
            merge(records + start, mid - start, records + start + mid - start, end - mid, Ls);
            for (int i = 0; i < end - start + 1; i++)
            {
                records[start + i] = Ls[i];
            }
        }
    }
}