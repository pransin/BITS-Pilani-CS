#include "insertionsort.h"
#include "quicksort.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

void testRun(Employee *empArray, int size, double results[]){
    // printf("%d\n", size);
    struct timeval t1, t2;
    Employee empArray1[size];
    Employee empArray2[size];
    for(int i = 0; i < size; i++){
        empArray1[i] = empArray2[i] = empArray[i];
    }

    gettimeofday(&t1, NULL);
    quickSort(empArray1, size, 0);
    gettimeofday(&t2, NULL);
    // results[0] = (t2.tv_sec - t1.tv_sec) * 1000000 + (t2.tv_usec - t1.tv_usec);
    results[0] = (t2.tv_sec - t1.tv_sec) * 1000.0 + (t2.tv_usec - t1.tv_usec) / 1000.0;

    gettimeofday(&t1, NULL);
    insertionSort(empArray2, size);
    gettimeofday(&t2, NULL);
    // results[1] = (t2.tv_sec - t1.tv_sec) * 1000000 + (t2.tv_usec - t1.tv_usec);
    results[1] = (t2.tv_sec - t1.tv_sec) * 1000.0 + (t2.tv_usec - t1.tv_usec) / 1000.0;
}


int estimateCutoff(Employee *empArray, int max){
    double results[2];
    // results[0] -> quickSort
    // results[1] -> insertionsort
    int min = 0;
    // testRun(empArray, min, results);
    testRun(empArray, max, results);

    if(results[0] > results[1]){
        return max;
    }
    // printf("%f %f\n", results[0], results[1]);
    int epsilon = 0;  // Epsilon decides the how close insertionsort can be to quicksort for mid to be a good cutoff size. 
    int mid = (min + max) / 2;
    while(min != max){
        
        if (results[0] - results[1] > epsilon){
            min = mid;
        }
        else if (results[0] - results[1] < -epsilon){
            max = mid;
        }
        else return mid;
        // printf("%f %f\n", results[0], results[1]);
        mid = (min + max) / 2;
        //  printf("%d\n", mid);


        testRun(empArray, mid, results);
    }
    return mid;

}
