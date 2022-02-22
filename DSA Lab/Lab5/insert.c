#include <stdlib.h>
#include <stdio.h>
#include "insert.h"

CREDIT_CARD *readRecords(FILE *records)
{
    int i = 0;
    int size = 10;
    CREDIT_CARD *card_array = (CREDIT_CARD *)malloc(size * sizeof(CREDIT_CARD));
    while (!feof(records))
    {
        if (i == size)
        {
            size *= 2;
            card_array = (CREDIT_CARD *)realloc(card_array, size * sizeof(CREDIT_CARD));
        }
        fscanf(records, "\"%llu, %[^,], %[^,], %[^,], %[^\"]\"\n",
               &card_array[i].cardno,
               card_array[i].bankcode,
               card_array[i].expirydate,
               card_array[i].firstname,
               card_array[i].lastname);
        i++;
    }
    return card_array;
}

void insertInOrder(CREDIT_CARD card, CREDIT_CARD *card_array, int curr_size)
{
    for (int i = curr_size - 2; i >= -1; i--)
    {
        if (i == -1 || card.cardno >= card_array[i].cardno)
        {
            card_array[i + 1] = card;
            break;
        }
        else
            card_array[i + 1] = card_array[i];
    }
}

void InsertionSort(CREDIT_CARD *card_array, int size)
{
    if (size == 1)
    {
        stackTop = (long long unsigned)&size;
        return;
    }
    InsertionSort(card_array, size - 1);
    insertInOrder(card_array[size - 1], card_array, size);
}