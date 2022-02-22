#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "bisection.h"
#include "employee.h"
#include "mixedSort.h"

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        printf("Please input 1st argument as input file and second argument as output file.\n");
        return 0;
    }

    FILE *inputfile = fopen(argv[1], "r");

    int input_size = atoi(argv[1]);
    if (inputfile == NULL)
    {
        printf("File cannot be opened.\n");
        return 0;
    }

    Employee empArray[input_size];
    for (int i = 0; i < input_size; i++)
        fscanf(inputfile, "%s %d\n", empArray[i].name, &empArray[i].empID);
    fclose(inputfile);
    int cutoff;
    if (input_size > 1000)
        cutoff = estimateCutoff(empArray, 1000);
    else
        cutoff = estimateCutoff(empArray, input_size);

    struct timeval t1, t2;
    double elapsedTime;

    gettimeofday(&t1, NULL);
    mixedSort(empArray, input_size, cutoff);
    gettimeofday(&t2, NULL);

    elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0;
    elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0;

    FILE *outputfile = fopen(argv[2], "w");

    fprintf(outputfile, "Time Taken to sort %d elements with mixedSort cutoff %d: %lf milliseconds.\n\n", input_size, cutoff, elapsedTime);

    printf("Time Taken to sort %d elements with mixedSort cutoff %d: %lf milliseconds.\n", input_size, cutoff, elapsedTime);

    for (int i = 0; i < input_size; i++)
    {
        fprintf(outputfile, "%s %d\n", empArray[i].name, empArray[i].empID);
    }
}