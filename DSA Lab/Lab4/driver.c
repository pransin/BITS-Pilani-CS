#include <stdio.h>
#include <stdlib.h>

#include <sys/time.h>
#include "2.h"
#include "cycle.h"    //includes linkedlist.h also

int main()
{
    struct timeval start, end;
    double elapsedTime;
    int N = 10000000;
    gettimeofday(&start, NULL);
    node *Ls = createList(N);
    createCycle(Ls);
    char iscyclic='F';
    if(testCyclic(Ls))
    iscyclic = 'T';
    myfree(Ls, N * sizeof(node));
    gettimeofday(&end, NULL);
    elapsedTime = (end.tv_sec - start.tv_sec) * 1000.0 
                + (end.tv_usec - start.tv_usec) / 1000.0;
    FILE* tocsv = fopen("observations.csv", "a");
    fprintf(tocsv, "%d,%lf,%u,%c\n", N, elapsedTime, spaceInHeap, iscyclic);  
    fclose(tocsv);             
}