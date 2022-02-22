#include "stack.h"
#include "employee.h"
#include <stdio.h>
#include <stdlib.h>

void swap(Employee *l, Employee *r)
{
    Employee temp = *l;
    *l = *r;
    *r = temp;
}
int partition(Employee empArray[], int l, int r)
{
    int pivot = empArray[r].empID;
    int i = l - 1;
    for (int j = l; j < r; j++)
    {
        if (empArray[j].empID <= pivot)
        {
            i++;
            swap(&empArray[i], &empArray[j]);
        }
    }
    swap(&empArray[i + 1], &empArray[r]);
    return i + 1;
}

void quickSort(Employee empArray[], int size, int S)
{
    int l, r;
    Stack *temp = newStack();
    push(temp, 0);
    push(temp, size - 1);
    while (temp->size > 0)
    {
        r = pop(temp);
        l = pop(temp);
        int p = partition(empArray, l, r);
        if (p - l > S)
        {
            push(temp, l);
            push(temp, p - 1);
        }

        if (r - p > S)
        {
            push(temp, p + 1);
            push(temp, r);
        }
    }
}