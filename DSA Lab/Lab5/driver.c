#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "insert.h"
// read, insertInOrder, insertionSort in insert.c

int main()
{
    struct timeval t1, t2;
    double elapsedTime;
    FILE *readtimes = fopen("readTime.txt", "w");
    FILE *sorttimes = fopen("sortTime.txt", "w");
    FILE *stackspace = fopen("stackSpace.txt", "w");
    for (int filenum = 10; filenum <= 100000; filenum *= 10)
    {
        long long unsigned stackBottom = (long long unsigned)&filenum;
        char filename[10];
        sprintf(filename, "%d", filenum); // Convert integer to string

        FILE *records = fopen(filename, "r");
        if (records == NULL)
        {
            printf("File cannot be opened.\n");
            exit(0);
        }

        // ************Loads the file into memory and records time taken**********************
        gettimeofday(&t1, NULL);
        CREDIT_CARD *card_array = readRecords(records);
        gettimeofday(&t2, NULL);
        elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0 + (t2.tv_usec - t1.tv_usec) / 1000.0;
        fprintf(readtimes, "Time taken to read %d values: %f ms.\n", filenum, elapsedTime);
        // *********************************************************************

        fclose(records);

        // *****************Insertion Sort and time taken*****************************
        gettimeofday(&t1, NULL);
        InsertionSort(card_array, filenum);
        gettimeofday(&t2, NULL);
        elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0 + (t2.tv_usec - t1.tv_usec) / 1000.0;
        fprintf(sorttimes, "Time taken to sort %d values: %f ms.\n", filenum, elapsedTime);
        //  **********************************************
        //&filenum gives bottom of the stack
        fprintf(stackspace, "Stack space used by insertion sort for %d values: %llu B.\n", filenum, stackBottom - stackTop);
        free(card_array);
    }
    fclose(readtimes);
    fclose(sorttimes);
    fclose(stackspace);
}